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


bool validateStartingParameters(System::String^ inputfileName, System::String^ outputfileName, bool dllType, System::String^ numberOfThreads,
	System::Windows::Forms::DataVisualization::Charting::Chart^ chart1, System::Windows::Forms::DataVisualization::Charting::Chart^ chart2);
void readBMP(Image* image, char* filename);
void saveBMP(Image* image, char* filename);
bool checkFileExtension(char* fileName);
void readLogFile(System::Windows::Forms::ListView^ listView);
void addToLogFile(System::Windows::Forms::ListView^ listView, std::string newMeasure);
HINSTANCE loadLibrary(bool isCppChosen);
void showHistogram(int* r, int* g, int* b, System::Windows::Forms::DataVisualization::Charting::Chart^ chart1);
void runFunction(HINSTANCE library, Image* image, short threadNumber);
#endif // !UTILITIES_H

