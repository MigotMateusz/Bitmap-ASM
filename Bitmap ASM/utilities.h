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

/* funkcja validateStartingParameters ma za zadanie sprawdzi� czy u�ytkownik wprowadzi� poprawne dane 
* inputfileName - to nazwa pliku wej�ciowego - program sprawdza czy plik jest rozszerzenia .bmp oraz czy plik o takiej nazwie istnieje
* outputfileName - to nazwa pliku wej�ciowego - program sprawdza czy plik jest rozszerzenia .bmp
* numberOfThreads - to liczba w�tk�w wybrana przez u�ytkownika - program sprawdza czy zosta�a wybrana oraz czy jest z przedzia�u od 1 do 64(w��cznie)
* funkcja zwraca warto�� false - je�li dane s� niepoprawne, true - je�li dane s� poprawne
*/
bool validateStartingParameters(System::String^ inputfileName, System::String^ outputfileName, System::String^ numberOfThreads);


/* funkcja readBMP ma za zadanie wczyta� bitmap�, kt�rego nazw� jest paramter filename i zapisa� do wska�nika image
* funkcja jest typu void i nie zwraca �adnej warto�ci
*/
void readBMP(Image* image, char* filename);

/* funkcja saveBMP ma za zadanie zapisa� bitmap�, kt�rego nazw� jest paramter filename i zapisa� ze wska�nika image, kt�re przechowuje dane bitmapy
* funkcja jest typu void i nie zwraca �adnej warto�ci
*/
void saveBMP(Image* image, char* filename);

/*funkcja checkFileExtension ma za zadanie sprawdzi� czy nazwa podana do funkcji poprzez parametr fileName typu char* ma rozszerzenie .bmp
* funkcja zwraca true je�li nazwa jest z rozszerzeniem .bmp lub false w przeciwnym wypadku
*/
bool checkFileExtension(char* fileName);

/*funkcja readLogFile ma za zadanie wczytanie z pliku tekstowego wszystkich zapisanych czas�w i wy�wietlenie tych danych na li�cie czas�w*/
void readLogFile(System::Windows::Forms::ListView^ listView);

/*funkcja addToLogFile ma za zadanie dodanie czasu wykonania si� algorytmu do pliku tekstowego oraz wy�wietlenie go na li�cie czas�w*/
void addToLogFile(System::Windows::Forms::ListView^ listView, std::string newMeasure);

/*funkcja loadLibrary ma za zadanie za�adowanie biblioteki w zale�no�ci od opcji, kt�r� wybra� u�ytkownik
* funkcja zwraca za�adowan� bibliotek�
*/
HINSTANCE loadLibrary(bool isCppChosen);

/* funkcja showHistogram ma za zadanie wy�wietli� dane z tablicy na wykresie, kt�ry jest elementem interfejsu graficznego g��wnego programu
* parametr r - jest to tablica przechowuj�ca histogram dla sk�adowej czerwonej, parametr g - jest to tablica przechowuj�ca histogram dla sk�adowej zielonej,
* parametr b - jest to tablica przechowuj�ca histogram dla sk�adowej niebieskiej
* parametr chart - to wykres na ktorym maj� wy�wietli� si� dane
*/
void showHistogram(int* r, int* g, int* b, System::Windows::Forms::DataVisualization::Charting::Chart^ chart1);

/*funkcja runBlurFunction ma za zadanie wykona� funkcj� rozmycia obrazu, przed wywo�aniem funkcji rozmycia, funkcja dzieli bitmap� na cz�ci,
* w zale�no�ci od wybranej liczby w�tk�w, a nast�pnie wywo�uje r�wnolegle(korzystaj�c z w�tk�w) funkcj� rozmycia
* parametr library - okre�la bibliotek�, z kt�rej ma wywo�a� funkcj�
* parametr image - to wska�nik na pocz�tek danych z bitmapy
* parametr threadNumber - to liczba w�tk�w, kt�ra ma zosta� u�yta do wykonania zadania
* funkcja zwraca wynik tj. zwraca czas wykonania si� rozmycia obrazu
*/

long long runBlurFunction(HINSTANCE library, Image* image, short threadNumber);

/*funkcja runHistogramFunction ma za zadanie obliczy� histogram, przed wywo�aniem histogramu, funkcja dzieli bitmap� na cz�ci,
* w zale�no�ci od wybranej liczby w�tk�w, a nast�pnie wywo�uje r�wnolegle(korzystaj�c z w�tk�w) histogram
* parametr library - okre�la bibliotek�, z kt�rej ma wywo�a� funkcj�
* parametr image - to wska�nik na pocz�tek danych z bitmapy
* parametr threadNumber - to liczba w�tk�w, kt�ra ma zosta� u�yta do wykonania zadania
* funkcja zwraca wynik tj. zwraca czas wykonania si� histogramu
*/

long long runHistogramFunction(HINSTANCE library, Image* image, short threadNumber, int* r, int* g, int* b);

//funkcja runFunctions ma za zadanie wywo�a� histogram przed rozmyciem, nast�pnie rozmycie obrazu, a na koniec histogram po rozmyciu obrazu

long long runFunctions(System::String^ inputfileName, System::String^ outputfileName, System::String^ numberOfThreads, bool dllType,
	System::Windows::Forms::DataVisualization::Charting::Chart^ chart1, System::Windows::Forms::DataVisualization::Charting::Chart^ chart2);

#endif // !UTILITIES_H

