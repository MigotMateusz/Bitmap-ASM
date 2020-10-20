#ifndef UTILITIES_H
#define UTILITIES_H
#include <windows.h>


struct Image
{
	PBITMAPFILEHEADER  file_header;
	PBITMAPINFOHEADER  info_header;
	int size;	
	char* data;
	BYTE* pixels;
};


bool validateStartingParameters(System::String^ inputfileName, System::String^ outputfileName, bool dllType, System::String^ numberOfThreads);
void readBMP(Image* image, char* filename);
void saveBMP(Image* image, char* filename);
bool checkFileExtension(char* fileName);
void readLogFile(System::Windows::Forms::ListView^ listView);
void addToLogFile(System::Windows::Forms::ListView^ listView, std::string newMeasure);
#endif // !UTILITIES_H

