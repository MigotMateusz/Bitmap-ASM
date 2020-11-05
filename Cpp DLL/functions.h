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
#ifdef CppDll_API
	#undef CppDll_API
	#define CppDll_API __declspec(dllexport)
#else
	#define CppDll_API __declspec(dllimport)
#endif
#include <string>


/*Funckja gaussBlur ma za zadanie rozmyæ obraz wed³ug algorytmu rozmycia gaussa
* parametr inputPixels - to wskaŸnik na dane bitmapy, parametr size - to rozmiar bitmapy, parametr imageWidth - to szerokoœc bitmapy
* paramert startHeight - to punkt na wysokoœci od którego funkcja ma dzia³aæ, parametr endHeight - to punkt na wysokoœci do którego funkcja ma dzia³aæ
*/
extern "C" void CppDll_API gaussBlur(BYTE * inputPixels, int size, int imageWidth, int startHeight, int endHeight);

/*Funckja histogram ma za zadanie obliczyæ histogram obrazu dla sk³adowych R, G i B
* parametr pixels - to wskaŸnik na dane bitmapy, parametry r,g,b to tablice do których zapisywany ma byæ histogram
* parametr imageWidth - to szerokoœc bitmapy
* paramert startHeight - to punkt na wysokoœci od którego funkcja ma dzia³aæ, parametr endHeight - to punkt na wysokoœci do którego funkcja ma dzia³aæ
*/
extern "C" void CppDll_API histogram(BYTE * pixels, int* r, int* g, int* b, int imageWidth, int startHeight, int endHeight);

