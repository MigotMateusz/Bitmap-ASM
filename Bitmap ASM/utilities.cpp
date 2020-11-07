/*-------------------------------------------------------------------- -
; ROZMYCIE OBRAZU I HISTOGRAM
; 06.11.2020 Mateusz Migot
; Informatyka SSI semestr 5 rok akademicki 2020 / 2021
; v.0.0.1 - stworzona solucja w visual studio 2019 (13.10.2020)
; v.0.0.2 - stworzony interfejs graficzny oraz wczytywanie i zapisywanie bitmapy(15.10.2020)
; v.0.1 - finalna wersja interfejsu graficznego oraz podstawowe funkcjonalnoœci programu g³ównego(20.10.2020)
; v.0.2.1 - dodanie CppDLL do projektu i po³¹czenie dynamiczne biblioteki z programem g³ównym(21.10.2020)
; v.0.2.2 - dodanie ASMDLL do projektu i po³¹czenie dynamiczne biblioteki z programem g³ówny(22.10.2020)
; v.0.2.3 - zaimplementowany algorytm obliczaj¹cy histogram obrazu(CppDLL) (22.10.2020)
; v.0.2.4 - zaimplementowany algorytm rozmycia obrazu(CppDLL) (24.10.2020)
; v.0.2.5 - dodanie równoleg³ego wykonywania siê funkcji(27.10.2020)
; v.0.3 - zaimplementowany algorytm obliczaj¹cy histogram obrazu(ASMDLL)(wersja 32 - bitowa) (29.10.2020)
; v.0.3.1 - zaimplementowany algorytm rozmycia obrazu(ASMDLL)(wersja 32 - bitowa) (02.11.2020)
; v.0.4 - zmiana projektu funkcji bibliotecznej(ASMDLL) na wersjê 64 - bitow¹(04.11.2020)
; v.0.5 - zmiana funkcji histogramu i funkcji rozmycia obrazu(ASM) na wersje 64 - bitowe(04.11.2020)
; v.0.5 - dodanie operacji wektorowych do histogramu(04.11.2020)
; v.0.6 - finalna wersja funkcji rozmycia obrazu(wykorzystuj¹ca operacje wektorowe) (05.11.2020)
; v.1.0 - finalna i aktualna wersja programu z wszystkimi funkcjonalnoœciami i zabezpieczeniami, zgodna z za³o¿eniami(05.11.2020)
; -------------------------------------------------------------------- - */
#include "pch.h"
#include <String>
#include <fstream>
#include <iostream>
#include <chrono>
#include <thread>
#include <vector>
#include "utilities.h"

typedef void(_stdcall* GuassBlur)(BYTE*, int, int, int, int);
typedef void(_stdcall* Histogram)(BYTE*, int*, int*, int*, int, int, int);

bool validateStartingParameters(System::String^ inputfileName, System::String^ outputfileName, System::String^ numberOfThreads){
	int length = inputfileName->Length;
	char* infileName = new char[length];
	sprintf(infileName, "%s", inputfileName);

	length = outputfileName->Length;
	char* outfileName = new char[length];
	sprintf(outfileName, "%s", outputfileName);

	char* pomThreads = new char[2];
	sprintf(pomThreads, "%s", numberOfThreads);

	if (!checkFileExtension(infileName) || !checkFileExtension(outfileName)) {
		System::Windows::Forms::MessageBox::Show("SprawdŸ czy plik jest rozszerzenia .bmp", "Niepoprawne wczytania pliku",
			System::Windows::Forms::MessageBoxButtons::OK);
		return false;
	}
		
	std::ifstream inputFile(infileName, std::ios::in | std::ios::binary | std::ios::ate);
	if (!inputFile) {
		System::Windows::Forms::MessageBox::Show("SprawdŸ czy plik z podan¹ nazw¹ istnieje i jest w poprawnym folderze.", "Niepoprawne wczytania pliku",
			System::Windows::Forms::MessageBoxButtons::OK);
		return false;
	}

	if (pomThreads[0] == '\0') {
		System::Windows::Forms::MessageBox::Show("Proszê wybraæ liczbê w¹tków do wykonania programu.", "Niepoprawna liczba w¹tków",
			System::Windows::Forms::MessageBoxButtons::OK);
		return false;
	} else if (atoi(pomThreads) <= 0 || atoi(pomThreads) > 64) {
		System::Windows::Forms::MessageBox::Show("Proszê wybraæ liczbê w¹tków w zakresie od 1 do 64.", "Niepoprawna liczba w¹tków",
			System::Windows::Forms::MessageBoxButtons::OK);
		return false;
	}
	else {
		length = strlen(pomThreads);
		for (int i = 0; i < length; i++) {
			if (!isdigit(pomThreads[i]))
			{
				System::Windows::Forms::MessageBox::Show("Proszê wybraæ liczbê w¹tków w zakresie od 1 do 64.", "Niepoprawna liczba w¹tków",
					System::Windows::Forms::MessageBoxButtons::OK);
				return false;
			}
		}	
		return true;
	}
	
}

long long runFunctions(System::String^ inputfileName, System::String^ outputfileName, System::String^ numberOfThreads, bool dllType, 
	System::Windows::Forms::DataVisualization::Charting::Chart^ chart1, System::Windows::Forms::DataVisualization::Charting::Chart^ chart2) {
	int length = inputfileName->Length;
	char* infileName = new char[length];
	sprintf(infileName, "%s", inputfileName);

	length = outputfileName->Length;
	char* outfileName = new char[length];
	sprintf(outfileName, "%s", outputfileName);

	char* pomThreads = new char[2];
	sprintf(pomThreads, "%s", numberOfThreads);
	int nThreads = atoi(pomThreads);

	Image* image = new Image;
	readBMP(image, infileName);
	HINSTANCE lib = loadLibrary(dllType);

	int red[256] = {}, green[256] = {}, blue[256] = {};
	int red1[256] = {}, green1[256] = {}, blue1[256] = {};

	long long time = 0;
	time += runHistogramFunction(lib, image, nThreads, red, green, blue);
	time += runBlurFunction(lib, image, nThreads);
	time += runHistogramFunction(lib, image, nThreads, red1, green1, blue1);
	showHistogram(red, green, blue, chart1);
	showHistogram(red1, green1, blue1, chart2);
	saveBMP(image, outfileName);
	return time;
}

void readBMP(Image* image, char* filename)
{
	std::ifstream inputFile(filename, std::ios::in | std::ios::binary | std::ios::ate);
	std::ifstream::pos_type end_of_file = inputFile.tellg();
	inputFile.seekg(0, std::ios::beg);

	image->size = end_of_file;
	image->data = new char[image->size];

	inputFile.read(image->data, image->size);
	image->file_header = PBITMAPFILEHEADER(image->data);
	image->info_header = PBITMAPINFOHEADER(image->data + sizeof(BITMAPFILEHEADER));
	image->pixels = reinterpret_cast<BYTE*>(image->data + image->file_header->bfOffBits);

	inputFile.close();
}

void saveBMP(Image* image, char* filename)
{
	std::ofstream outputFile(filename, std::ios::out | std::ios::binary);
	outputFile.write(image->data, image->size);
	outputFile.close();
}

bool checkFileExtension(char* fileName) {
	std::string extension = "";
	bool dotAppeared = false;
	for (int i = 0; i < strlen(fileName); i++) {
		if (fileName[i] == '.')
			dotAppeared = true;
		
		if (dotAppeared == true)
			extension += fileName[i];
	}
	if (extension == ".bmp")
		return true;
	else
		return false;
}

void readLogFile(System::Windows::Forms::ListView^ listView) {
	std::string dataLine;
	std::ifstream inputFile("measures.txt", std::ios::in);
	while (!inputFile.eof()) {
		std::getline(inputFile, dataLine);
		System::String^ text = gcnew System::String(dataLine.c_str());
		listView->Items->Add(text);
	}
	inputFile.close(); 
}

void addToLogFile(System::Windows::Forms::ListView^ listView, std::string newMeasure,
	bool isCppChosen, System::String^ numberOfThreads) {
	System::String^ library;
	if (isCppChosen)
		library = "CppDLL";
	else
		library = "ASMDLL";
	System::String^ text = gcnew System::String(newMeasure.c_str()) + " " + library + " " +" Liczba w¹tków -> " + numberOfThreads;
	listView->Items->Add(text);
	int length = text->Length;
	char* textChar = new char[length];
	sprintf(textChar, "%s", text);
	std::fstream outputFile("measures.txt", std::ios::app);
	outputFile << std::endl << textChar;
	outputFile.close();
}

HINSTANCE loadLibrary(bool isCppChosen) {
	HINSTANCE lib;
	if (isCppChosen)
		lib = LoadLibraryA("CppDLL.dll");
	else
		lib = LoadLibraryA("ASMDLL.dll");	 
	return lib;
}

void showHistogram(int* r, int* g, int* b, System::Windows::Forms::DataVisualization::Charting::Chart^ chart1) {
	chart1->Series[0]->Points->Clear();
	chart1->Series[1]->Points->Clear();
	chart1->Series[2]->Points->Clear();
	for (int i = 0; i < 256; i++) {
		chart1->Series[0]->Points->AddXY(i, b[i]);
		chart1->Series[1]->Points->AddXY(i, g[i]);
		chart1->Series[2]->Points->AddXY(i, r[i]);
	}
}

long long runBlurFunction(HINSTANCE library, Image* image, short threadNumber) {
	GuassBlur gaussBlur1 = (GuassBlur)GetProcAddress(library, "gaussBlur");
	int divideParts = image->info_header->biHeight / threadNumber;	
	std::thread *threads = new std::thread[threadNumber];

	for (int i = 0; i < threadNumber - 1; i++)
		threads[i] = std::thread(gaussBlur1, image->pixels, image->size, image->info_header->biWidth, i * divideParts, (i + 1) * divideParts);

	threads[threadNumber - 1] = std::thread(gaussBlur1, image->pixels, image->size, image->info_header->biWidth, (threadNumber - 1) * divideParts, 
		image->info_header->biHeight - 1);

	std::chrono::high_resolution_clock::time_point begin = std::chrono::high_resolution_clock::now();

	for (int i = 0; i < threadNumber; i++)
		threads[i].join();

	std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();

	auto time = std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count();
	std::cerr << "Time Blur: " << time << std::endl;
	return time;
}

long long runHistogramFunction(HINSTANCE library, Image* image, short threadNumber, int* r, int* g, int* b) {
	Histogram histogram2 = (Histogram)GetProcAddress(library, "histogram");
	int divideParts = image->info_header->biHeight / threadNumber;
	std::thread* threads = new std::thread[threadNumber];

	for (int i = 0; i < threadNumber - 1; i++)
		threads[i] = std::thread(histogram2, image->pixels, r, g, b, image->info_header->biWidth, i * divideParts, (i + 1) * divideParts);

	threads[threadNumber - 1] = std::thread(histogram2, image->pixels, r, g, b, image->info_header->biWidth, (threadNumber - 1) * divideParts,
		image->info_header->biHeight - 1);

	std::chrono::high_resolution_clock::time_point begin = std::chrono::high_resolution_clock::now();

	for (int i = 0; i < threadNumber; i++)
		threads[i].join();

	std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();

	auto time = std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count();
	std::cerr << "Time histogram: " << time << std::endl;
	return time;
}
