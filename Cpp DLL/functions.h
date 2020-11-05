/*-------------------------------------------------------------------- -
; ROZMYCIE OBRAZU I HISTOGRAM
; 06.11.2020 Mateusz Migot
; Informatyka SSI semestr 5 rok akademicki 2020 / 2021
; v.0.0.1 - stworzona solucja w visual studio 2019 (13.10.2020)
; v.0.0.2 - stworzony interfejs graficzny oraz wczytywanie i zapisywanie bitmapy(15.10.2020)
; v.0.1 - finalna wersja interfejsu graficznego oraz podstawowe funkcjonalno�ci programu g��wnego(20.10.2020)
; v.0.2.1 - dodanie CppDLL do projektu i po��czenie dynamiczne biblioteki z programem g��wnym(21.10.2020)
; v.0.2.2 - dodanie ASMDLL do projektu i po��czenie dynamiczne biblioteki z programem g��wny(22.10.2020)
; v.0.2.3 - zaimplementowany algorytm obliczaj�cy histogram obrazu(CppDLL) (22.10.2020)
; v.0.2.4 - zaimplementowany algorytm rozmycia obrazu(CppDLL) (24.10.2020)
; v.0.2.5 - dodanie r�wnoleg�ego wykonywania si� funkcji(27.10.2020)
; v.0.3 - zaimplementowany algorytm obliczaj�cy histogram obrazu(ASMDLL)(wersja 32 - bitowa) (29.10.2020)
; v.0.3.1 - zaimplementowany algorytm rozmycia obrazu(ASMDLL)(wersja 32 - bitowa) (02.11.2020)
; v.0.4 - zmiana projektu funkcji bibliotecznej(ASMDLL) na wersj� 64 - bitow�(04.11.2020)
; v.0.5 - zmiana funkcji histogramu i funkcji rozmycia obrazu(ASM) na wersje 64 - bitowe(04.11.2020)
; v.0.5 - dodanie operacji wektorowych do histogramu(04.11.2020)
; v.0.6 - finalna wersja funkcji rozmycia obrazu(wykorzystuj�ca operacje wektorowe) (05.11.2020)
; v.1.0 - finalna i aktualna wersja programu z wszystkimi funkcjonalno�ciami i zabezpieczeniami, zgodna z za�o�eniami(05.11.2020)
; -------------------------------------------------------------------- - */
#ifdef CppDll_API
	#undef CppDll_API
	#define CppDll_API __declspec(dllexport)
#else
	#define CppDll_API __declspec(dllimport)
#endif
#include <string>


/*Funckja gaussBlur ma za zadanie rozmy� obraz wed�ug algorytmu rozmycia gaussa
* parametr inputPixels - to wska�nik na dane bitmapy, parametr size - to rozmiar bitmapy, parametr imageWidth - to szeroko�c bitmapy
* paramert startHeight - to punkt na wysoko�ci od kt�rego funkcja ma dzia�a�, parametr endHeight - to punkt na wysoko�ci do kt�rego funkcja ma dzia�a�
*/
extern "C" void CppDll_API gaussBlur(BYTE * inputPixels, int size, int imageWidth, int startHeight, int endHeight);

/*Funckja histogram ma za zadanie obliczy� histogram obrazu dla sk�adowych R, G i B
* parametr pixels - to wska�nik na dane bitmapy, parametry r,g,b to tablice do kt�rych zapisywany ma by� histogram
* parametr imageWidth - to szeroko�c bitmapy
* paramert startHeight - to punkt na wysoko�ci od kt�rego funkcja ma dzia�a�, parametr endHeight - to punkt na wysoko�ci do kt�rego funkcja ma dzia�a�
*/
extern "C" void CppDll_API histogram(BYTE * pixels, int* r, int* g, int* b, int imageWidth, int startHeight, int endHeight);

