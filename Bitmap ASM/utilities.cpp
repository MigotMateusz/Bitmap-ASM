#include "pch.h"
#include <String>
#include <fstream>
#include <iostream>
#include <chrono>
#include <thread>
#include <vector>
#include "utilities.h"

typedef int(_stdcall* MyProc)(int, int);
typedef void(_stdcall* MyFunc1)(BYTE*, int, int*, int*, int*);
typedef void(_stdcall* MyFunc2)(BYTE*, int, int, int, int);
typedef void(_stdcall* Pom1)(BYTE*, int, int, int, int*, int*, int*);

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

	else if (pomThreads[0] == '\0') {
		System::Windows::Forms::MessageBox::Show("Proszê wybraæ liczbê w¹tków do wykonania programu.", "Niepoprawna liczba w¹tków",
			System::Windows::Forms::MessageBoxButtons::OK);
		return false;
	}

	else
		return true;
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

	Image* image = new Image;
	readBMP(image, infileName);
	HINSTANCE lib = loadLibrary(dllType);
	MyFunc1 histogram = (MyFunc1)GetProcAddress(lib, "histogram");
	MyFunc2 gaussBlur = (MyFunc2)GetProcAddress(lib, "gaussBlur");
	int red[256] = {}, green[256] = {}, blue[256] = {};
	int red1[256] = {}, green1[256] = {}, blue1[256] = {};
	std::chrono::high_resolution_clock::time_point begin = std::chrono::high_resolution_clock::now();
	histogram(image->pixels, image->size, red, green, blue);
	runFunction(lib, image, 2, red1, green1, blue1);
	//histogram(image->pixels, image->size, red1, green1, blue1);
	std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();
	auto time = std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count();
	std::cerr << "Time: " << time << std::endl;
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

void addToLogFile(System::Windows::Forms::ListView^ listView, std::string newMeasure) {
	System::String^ text = gcnew System::String(newMeasure.c_str());
	listView->Items->Add(text);
	std::fstream outputFile("measures.txt", std::ios::app);
	outputFile << std::endl << newMeasure;
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
	for (int i = 0; i < 256; i++) {
		chart1->Series[0]->Points->AddXY(i, b[i]);
		chart1->Series[1]->Points->AddXY(i, g[i]);
		chart1->Series[2]->Points->AddXY(i, r[i]);
	}
}

void runFunction(HINSTANCE library, Image* image, short threadNumber, int* r, int* g, int* b) {
	MyFunc2 gaussBlur1 = (MyFunc2)GetProcAddress(library, "gaussBlur");
	Pom1 histogram2 = (Pom1)GetProcAddress(library, "histogram2");
	int divideParts = image->info_header->biHeight / threadNumber;	
	std::thread *threads = new std::thread[threadNumber];
	for (int i = 0; i < threadNumber - 1; i++) {
		threads[i] = std::thread(gaussBlur1, image->pixels, image->size, image->info_header->biWidth, i * divideParts, (i + 1) * divideParts);
	}
	threads[threadNumber - 1] = std::thread(gaussBlur1, image->pixels, image->size, image->info_header->biWidth, (threadNumber - 1) * divideParts, 
		image->info_header->biHeight - 1);
	for (int i = 0; i < threadNumber - 1; i++) {
		threads[i].join();
	}
	
	std::thread* threads2 = new std::thread[threadNumber];
	for (int i = 0; i < threadNumber - 1; i++) {
		threads2[i] = std::thread(histogram2, image->pixels, image->info_header->biWidth, i*divideParts, (i+1)*divideParts, r, g, b);
	}
	threads2[threadNumber - 1] = std::thread(histogram2, image->pixels, image->info_header->biWidth, (threadNumber - 1) * divideParts, image->info_header->biHeight - 1
		, r, g, b);
	for (int i = 0; i < threadNumber - 1; i++) {
		threads2[i].join();
	}
}