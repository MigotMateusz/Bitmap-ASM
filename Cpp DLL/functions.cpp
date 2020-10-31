/*
* Rozmycie obrazu i histogram
* 29.10.2020
* Mateusz Migot
* Informatyka SSI rok 3 sem.5
* v0.2 - dzia³aj¹ce funkcje biblioteczne napisane w jêzyku wysokiego poziomu, skoñczone GUI programu g³ównego
* Zmiany wzglêdem v0.1 - dodana implementacja w¹tków oraz zapis czasu wykonania siê funkcji do pliku
*/
#include "pch.h"
#include <string>
#include <iostream>
#include "functions.h"

void histogram(BYTE* pixels, int size, int *r, int *g, int* b) {
	for (int i = 0; i < size - 3; i += 3) {
		b[(int)pixels[i]]++;
		g[(int)pixels[i + 1]]++;
		r[(int)pixels[i + 2]]++;
	}
}

void histogram2(BYTE* pixels, int imageWidth, int startHeight, int endHeight, int* r, int* g, int* b) {
	int width = imageWidth * 3;
	for (int i = width * startHeight; i < width * endHeight - 2; i += 3) {
		b[(int)pixels[i]]++;
		g[(int)pixels[i + 1]]++;
		r[(int)pixels[i + 2]]++;
	}
}

void gaussBlur(BYTE* inputPixels,int size, int imageWidth, int startHeight, int endHeight) {
	int matrix[] = {
	1, 2, 1,
	2, 4, 2,
	1, 2, 1
	};
	int width = imageWidth * 3;
	for (int i = width * startHeight; i < width * endHeight; i += 3) {
		if ((i - width - 3) >= 0 && (i - width + 3) >= 0 && (i - width + 3) < size && (i + width - 3) >= 0 && (i + width - 3) < size) {
			int newPixel1 = inputPixels[i - width - 3] * matrix[0] + inputPixels[i - width] * matrix[1] + inputPixels[i - width + 3] * matrix[2] +
				inputPixels[i - 3] * matrix[3] + inputPixels[i] * matrix[4] + inputPixels[i + 3] * matrix[5] +
				inputPixels[i + width - 3] * matrix[6] + inputPixels[i + width] * matrix[7] + inputPixels[i + width + 3] * matrix[8];
			int newPixel2 = inputPixels[i + 1 - width - 3] * matrix[0] + inputPixels[i + 1 - width] * matrix[1] + inputPixels[i + 1 - width + 3] * matrix[2] +
				inputPixels[i + 1 - 3] * matrix[3] + inputPixels[i + 1] * matrix[4] + inputPixels[i + 1 + 3] * matrix[5] +
				inputPixels[i + 1 + width - 3] * matrix[6] + inputPixels[i + 1 + width] * matrix[7] + inputPixels[i + 1 + width + 3] * matrix[8];
			int newPixel3 = inputPixels[i + 2 - width - 3] * matrix[0] + inputPixels[i + 2 - width] * matrix[1] + inputPixels[i + 2 - width + 3] * matrix[2] +
				inputPixels[i + 2 - 3] * matrix[3] + inputPixels[i + 2] * matrix[4] + inputPixels[i + 2 + 3] * matrix[5] +
				inputPixels[i + 2 + width - 3] * matrix[6] + inputPixels[i + 2 + width] * matrix[7] + inputPixels[i + 2 + width + 3] * matrix[8];
			inputPixels[i] = newPixel1 / 16;
			inputPixels[i + 1] = newPixel2 / 16;
			inputPixels[i + 2] = newPixel3 / 16;
		}
	}
}

void gaussBlur1(BYTE* inputPixels, int size, int imageWidth, int startHeight, int endHeight) {
	int oneDimensionalKernel[3] = { 1, 2, 1 };
	int width = imageWidth * 3;
	for (int i = width * startHeight; i < width * endHeight; i += 3) {
		if ((i - width - 3) >= 0 && (i + width + 3) < size) {
			int newPixel1 = inputPixels[i - 3] * oneDimensionalKernel[0] + inputPixels[i] * oneDimensionalKernel[1] + inputPixels[i + 3] * oneDimensionalKernel[2] +
				inputPixels[i - width - 3] * oneDimensionalKernel[0] + inputPixels[i] * oneDimensionalKernel[1] + inputPixels[i + width + 3] * oneDimensionalKernel[2];
			int newPixel2 = inputPixels[i + 1 - 3] * oneDimensionalKernel[0] + inputPixels[i + 1] * oneDimensionalKernel[1] + inputPixels[i + 1 + 3] * oneDimensionalKernel[2] +
				inputPixels[i - width + 1 - 3] * oneDimensionalKernel[0] + inputPixels[i + 1] * oneDimensionalKernel[1] + inputPixels[i + width + 1 + 3] * oneDimensionalKernel[2];
			int newPixel3 = inputPixels[i + 2 - 3] * oneDimensionalKernel[0] + inputPixels[i + 2] * oneDimensionalKernel[1] + inputPixels[i + 2 + 3] * oneDimensionalKernel[1] + 
				inputPixels[i - width + 2 - 3] * oneDimensionalKernel[0] + inputPixels[i + 2] * oneDimensionalKernel[1] + inputPixels[i + width + 2 + 3] * oneDimensionalKernel[1];
			inputPixels[i] = newPixel1 / 16;
			inputPixels[i + 1] = newPixel2 / 16;
			inputPixels[i + 2] = newPixel3 / 16;
		}
	}
}