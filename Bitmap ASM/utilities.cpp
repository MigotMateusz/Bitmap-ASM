#include "pch.h"
#include <String>
#include <fstream>
#include <iostream>
#include "utilities.h"

typedef std::string(_stdcall* MYPROC)();
typedef int(_stdcall* MyProc)(int, int);

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
		histogram(image, chart1);
		//tutaj rozmycie
		gaussBlur(image);
		histogram(image, chart2);
		//saveBMP(image, outfileName);
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

void histogram(Image* image, System::Windows::Forms::DataVisualization::Charting::Chart^ chart1) {
	int r[256] = {},
		g[256] = {},
		b[256] = {};
	for (int i = 0; i < image->size-3; i+=3) {	
		b[(int)image->pixels[i]]++;
		g[(int)image->pixels[i + 1]]++;
		r[(int)image->pixels[i + 2]]++;
	}
	for (int i = 0; i < 256; i++) {
		chart1->Series[0]->Points->AddXY(i, b[i]);
		chart1->Series[1]->Points->AddXY(i, g[i]);
		chart1->Series[2]->Points->AddXY(i, r[i]);
	}
		
}
void gaussBlur(Image* image) {
	int matrix[] = {
		1, 2, 1,
		2, 4, 2,
		1, 2, 1
	};
	int length = image->info_header->biWidth * 3;
	int size = image->size - image->file_header->bfOffBits;
	for (int i = 0; i < size; i += 3) {
		if((i - length - 3) >= 0 && (i - length + 3) >= 0 && (i - length + 3) < size && (i + length - 3)>=0 && (i + length - 3) < size)
			int newPixel = image->pixels[i - length - 3] * matrix[0] + image->pixels[i - length] * matrix[1] + image->pixels[i - length + 3] * matrix[2] +
				image->pixels[i - 3] * matrix[3] + image->pixels[i] * matrix[4] + image->pixels[i + 3] * matrix[5] +
				image->pixels[i + length - 3] * matrix[6] + image->pixels[i + length] * matrix[7] + image->pixels[i + length + 3] * matrix[8];
			image->pixels[i];

	}
}