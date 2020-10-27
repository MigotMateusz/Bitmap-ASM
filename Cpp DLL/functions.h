/*
* Rozmycie obrazu i histogram
* 29.10.2020 
* Mateusz Migot
* Informatyka SSI rok 3 sem.5
* v0.2 - dzia�aj�ce funkcje biblioteczne napisane w j�zyku wysokiego poziomu, sko�czone GUI programu g��wnego
* Zmiany wzgl�dem v0.1 - dodana implementacja w�tk�w oraz zapis czasu wykonania si� funkcji do pliku
*/
#pragma once

#ifdef CppDll_API_EXPORTS
	#define CppDll_API __declspec(dllexport)
#else
	#define CppDll_API __declspec(dllimport)
#endif
#include <string>

extern "C" void CppDll_API histogram(BYTE * pixels, int size, int* r, int* g, int* b);
extern "C" void CppDll_API gaussBlur(BYTE * inputPixels, int size, int imageWidth, int startHeight, int endHeight);
extern "C" void CppDll_API gaussBlur1(BYTE * inputPixels, int size, int imageWidth, int startHeight, int endHeight);
extern "C" void CppDll_API histogram2(BYTE * pixels, int imageWidth, int startHeight, int endHeight, int* r, int* g, int* b);
