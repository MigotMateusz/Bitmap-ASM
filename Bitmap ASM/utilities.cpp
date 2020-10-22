#include "pch.h"
#include <String>
#include <fstream>
#include "utilities.h"

typedef std::string(_stdcall* MYPROC)();
typedef int(_stdcall* MyProc)(int, int);

bool validateStartingParameters(System::String^ inputfileName, System::String^ outputfileName, bool dllType, System::String^ numberOfThreads){
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
		readBMP(image,infileName);
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



void loadLibrary(System::Windows::Forms::ListView^ listView) {
	/*HINSTANCE hinstLib = LoadLibraryA("CppDLL.dll");
	
	if (hinstLib != NULL) {
		MYPROC ProcAdd = (MYPROC)GetProcAddress(hinstLib, "test");
		if(ProcAdd != NULL)
			listView->Items->Add(gcnew System::String(ProcAdd().c_str()));
	}
	FreeLibrary(hinstLib);*/
	HINSTANCE lib = LoadLibraryA("ASMDLL.dll");
	if (lib != NULL) {
		MyProc function = (MyProc)GetProcAddress(lib, "MyProc1");
		listView->Items->Add(gcnew System::String(std::to_string(function(5,3)).c_str()));
	}
	//MyProc1 dodawanie = (MyProc1)GetProcAddress(dyn_asm, "MyProc1");
	//dodawanie();
	//listView->Items->Add(gcnew System::String(std::to_string(wynik).c_str()));
}