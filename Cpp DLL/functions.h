#pragma once

#ifdef CppDll_API_EXPORTS
	#define CppDll_API __declspec(dllexport)
#else
	#define CppDll_API __declspec(dllimport)
#endif
#include <string>

extern "C" void CppDll_API histogram(BYTE * pixels, int size, int* r, int* g, int* b);
extern "C" void CppDll_API gaussBlur(BYTE * inputPixels, int size, int imageWidth, int startHeight, int endHeight);
