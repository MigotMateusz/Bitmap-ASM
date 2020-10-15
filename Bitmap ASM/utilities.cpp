#include "pch.h"
#include <String>
#include <fstream>
#include "utilities.h"
bool validateStartingParameters(System::String^ nameOfFile, System::String^ numberOfThreads){
	int length = nameOfFile->Length;
	char* fileName = new char[length];
	sprintf(fileName, "%s", nameOfFile);
	char* pomThreads = new char[2];
	sprintf(pomThreads, "%s", numberOfThreads);
	std::ifstream inputFile(fileName, std::ios::in | std::ios::binary | std::ios::ate);
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
		readBMP(image,fileName);
		saveBMP(image);
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
void saveBMP(Image* image)
{
	std::ofstream outputFile("result1.bmp", std::ios::out | std::ios::binary);
	outputFile.write(image->data, image->size);
	outputFile.close();
}