/*-------------------------------------------------------------------- -
; ROZMYCIE OBRAZU I HISTOGRAM
; 06.11.2020 Mateusz Migot
; Informatyka SSI semestr 5 rok akademicki 2020 / 2021
; v.0.0.1 - stworzona solucja w visual studio 2019 (13.10.2020)
; v.0.0.2 - stworzony interfejs graficzny oraz wczytywanie i zapisywanie bitmapy(15.10.2020)
; v.0.1 - finalna wersja interfejsu graficznego oraz podstawowe funkcjonalnoœci programu g³ównego(20.10.2020)
; v.0.2.1 - dodanie CppDLL do projektu i po³¹czenie dynamiczne biblioteki z programem g³ównym(21.10.2020)
; v.0.2.2 - dodanie ASMDLL do projektu i po³¹czenie dynamiczne biblioteki z programem g³ówny(22.10.2020)
; v.0.2.3 - zaimplementowany algorytm obliczaj¹cy histogram obrazu(CppDLL) (22.10.2020)
; v.0.2.4 - zaimplementowany algorytm rozmycia obrazu(CppDLL) (24.10.2020)
; v.0.2.5 - dodanie równoleg³ego wykonywania siê funkcji(27.10.2020)
; v.0.3 - zaimplementowany algorytm obliczaj¹cy histogram obrazu(ASMDLL)(wersja 32 - bitowa) (29.10.2020)
; v.0.3.1 - zaimplementowany algorytm rozmycia obrazu(ASMDLL)(wersja 32 - bitowa) (02.11.2020)
; v.0.4 - zmiana projektu funkcji bibliotecznej(ASMDLL) na wersjê 64 - bitow¹(04.11.2020)
; v.0.5 - zmiana funkcji histogramu i funkcji rozmycia obrazu(ASM) na wersje 64 - bitowe(04.11.2020)
; v.0.5 - dodanie operacji wektorowych do histogramu(04.11.2020)
; v.0.6 - finalna wersja funkcji rozmycia obrazu(wykorzystuj¹ca operacje wektorowe) (05.11.2020)
; v.1.0 - finalna i aktualna wersja programu z wszystkimi funkcjonalnoœciami i zabezpieczeniami, zgodna z za³o¿eniami(05.11.2020)
; -------------------------------------------------------------------- - */
#include "pch.h"
#include <string>
#include <iostream>
#include "functions.h"

void histogram(BYTE* pixels, int* r, int* g, int* b, int imageWidth, int startHeight, int endHeight) {
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