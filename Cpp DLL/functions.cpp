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
void gaussBlur(BYTE* inputPixels,int size, int imageWidth) {
	int matrix[] = {
	1, 2, 1,
	2, 4, 2,
	1, 2, 1
	};
	int length = imageWidth * 3;
	for (int i = 0; i < size; i += 3) {
		if ((i - length - 3) >= 0 && (i - length + 3) >= 0 && (i - length + 3) < size && (i + length - 3) >= 0 && (i + length - 3) < size) {
			int newPixel1 = inputPixels[i - length - 3] * matrix[0] + inputPixels[i - length] * matrix[1] + inputPixels[i - length + 3] * matrix[2] +
				inputPixels[i - 3] * matrix[3] + inputPixels[i] * matrix[4] + inputPixels[i + 3] * matrix[5] +
				inputPixels[i + length - 3] * matrix[6] + inputPixels[i + length] * matrix[7] + inputPixels[i + length + 3] * matrix[8];
			int newPixel2 = inputPixels[i + 1 - length - 3] * matrix[0] + inputPixels[i + 1 - length] * matrix[1] + inputPixels[i + 1 - length + 3] * matrix[2] +
				inputPixels[i + 1 - 3] * matrix[3] + inputPixels[i + 1] * matrix[4] + inputPixels[i + 1 + 3] * matrix[5] +
				inputPixels[i + 1 + length - 3] * matrix[6] + inputPixels[i + 1 + length] * matrix[7] + inputPixels[i + 1 + length + 3] * matrix[8];
			int newPixel3 = inputPixels[i + 2 - length - 3] * matrix[0] + inputPixels[i + 2 - length] * matrix[1] + inputPixels[i + 2 - length + 3] * matrix[2] +
				inputPixels[i + 2 - 3] * matrix[3] + inputPixels[i + 2] * matrix[4] + inputPixels[i + 2 + 3] * matrix[5] +
				inputPixels[i + 2 + length - 3] * matrix[6] + inputPixels[i + 2 + length] * matrix[7] + inputPixels[i + 2 + length + 3] * matrix[8];
			inputPixels[i] = newPixel1 / 16;
			inputPixels[i + 1] = newPixel2 / 16;
			inputPixels[i + 2] = newPixel3 / 16;
		}

		

	}
}