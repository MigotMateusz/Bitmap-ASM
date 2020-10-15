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


bool validateStartingParameters(System::String^ fileName, System::String^ numberOfThreads);
void readBMP(Image* image, char* filename);
void saveBMP(Image* image);
#endif // !UTILITIES_H

