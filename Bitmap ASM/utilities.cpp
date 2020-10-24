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
typedef void(_stdcall* MyFunc2)(BYTE*, int, int);

bool validateStartingParameters(System::String^ inputfileName, System::String^ outputfileName, bool dllType, System::String^ numberOfThreads,
	System::Windows::Forms::DataVisualization::Charting::Chart^ chart1, System::Windows::Forms::DataVisualization::Charting::Chart^ chart2){
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

	else {
		Image* image = new Image;
		readBMP(image, infileName);
		HINSTANCE lib = loadLibrary(dllType);
		MyFunc1 histogram = (MyFunc1)GetProcAddress(lib, "histogram");
		MyFunc2 gaussBlur = (MyFunc2)GetProcAddress(lib, "gaussBlur");
		int red[256] = {}, green[256] = {}, blue[256] = {};
		int red1[256] = {}, green1[256] = {}, blue1[256] = {};
		std::chrono::high_resolution_clock::time_point begin = std::chrono::high_resolution_clock::now();
		histogram(image->pixels, image->size, red, green, blue);
		gaussBlur(image->pixels, image->size, image->info_header->biWidth);
		histogram(image->pixels, image->size, red1, green1, blue1);
		std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();
		auto time = std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count();
		std::cerr << "Time: " << time << std::endl;
		showHistogram(red, green, blue, chart1);
		showHistogram(red1, green1, blue1, chart2);
		saveBMP(image, outfileName);
		return true;
	}		
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
