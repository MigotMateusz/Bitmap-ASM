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

/* funkcja validateStartingParameters ma za zadanie sprawdziæ czy u¿ytkownik wprowadzi³ poprawne dane 
* inputfileName - to nazwa pliku wejœciowego - program sprawdza czy plik jest rozszerzenia .bmp oraz czy plik o takiej nazwie istnieje
* outputfileName - to nazwa pliku wejœciowego - program sprawdza czy plik jest rozszerzenia .bmp
* numberOfThreads - to liczba w¹tków wybrana przez u¿ytkownika - program sprawdza czy zosta³a wybrana oraz czy jest z przedzia³u od 1 do 64(w³¹cznie)
* funkcja zwraca wartoœæ false - jeœli dane s¹ niepoprawne, true - jeœli dane s¹ poprawne
*/
bool validateStartingParameters(System::String^ inputfileName, System::String^ outputfileName, System::String^ numberOfThreads);


/* funkcja readBMP ma za zadanie wczytaæ bitmapê, którego nazw¹ jest paramter filename i zapisaæ do wskaŸnika image
* funkcja jest typu void i nie zwraca ¿adnej wartoœci
*/
void readBMP(Image* image, char* filename);

/* funkcja saveBMP ma za zadanie zapisaæ bitmapê, którego nazw¹ jest paramter filename i zapisaæ ze wskaŸnika image, które przechowuje dane bitmapy
* funkcja jest typu void i nie zwraca ¿adnej wartoœci
*/
void saveBMP(Image* image, char* filename);

/*funkcja checkFileExtension ma za zadanie sprawdziæ czy nazwa podana do funkcji poprzez parametr fileName typu char* ma rozszerzenie .bmp
* funkcja zwraca true jeœli nazwa jest z rozszerzeniem .bmp lub false w przeciwnym wypadku
*/
bool checkFileExtension(char* fileName);

/*funkcja readLogFile ma za zadanie wczytanie z pliku tekstowego wszystkich zapisanych czasów i wyœwietlenie tych danych na liœcie czasów*/
void readLogFile(System::Windows::Forms::ListView^ listView);

/*funkcja addToLogFile ma za zadanie dodanie czasu wykonania siê algorytmu do pliku tekstowego oraz wyœwietlenie go na liœcie czasów*/
void addToLogFile(System::Windows::Forms::ListView^ listView, std::string newMeasure);

/*funkcja loadLibrary ma za zadanie za³adowanie biblioteki w zale¿noœci od opcji, któr¹ wybra³ u¿ytkownik
* funkcja zwraca za³adowan¹ bibliotekê
*/
HINSTANCE loadLibrary(bool isCppChosen);

/* funkcja showHistogram ma za zadanie wyœwietliæ dane z tablicy na wykresie, który jest elementem interfejsu graficznego g³ównego programu
* parametr r - jest to tablica przechowuj¹ca histogram dla sk³adowej czerwonej, parametr g - jest to tablica przechowuj¹ca histogram dla sk³adowej zielonej,
* parametr b - jest to tablica przechowuj¹ca histogram dla sk³adowej niebieskiej
* parametr chart - to wykres na ktorym maj¹ wyœwietliæ siê dane
*/
void showHistogram(int* r, int* g, int* b, System::Windows::Forms::DataVisualization::Charting::Chart^ chart1);

/*funkcja runBlurFunction ma za zadanie wykonaæ funkcjê rozmycia obrazu, przed wywo³aniem funkcji rozmycia, funkcja dzieli bitmapê na czêœci,
* w zale¿noœci od wybranej liczby w¹tków, a nastêpnie wywo³uje równolegle(korzystaj¹c z w¹tków) funkcjê rozmycia
* parametr library - okreœla bibliotekê, z której ma wywo³aæ funkcjê
* parametr image - to wskaŸnik na pocz¹tek danych z bitmapy
* parametr threadNumber - to liczba w¹tków, która ma zostaæ u¿yta do wykonania zadania
* funkcja zwraca wynik tj. zwraca czas wykonania siê rozmycia obrazu
*/

long long runBlurFunction(HINSTANCE library, Image* image, short threadNumber);

/*funkcja runHistogramFunction ma za zadanie obliczyæ histogram, przed wywo³aniem histogramu, funkcja dzieli bitmapê na czêœci,
* w zale¿noœci od wybranej liczby w¹tków, a nastêpnie wywo³uje równolegle(korzystaj¹c z w¹tków) histogram
* parametr library - okreœla bibliotekê, z której ma wywo³aæ funkcjê
* parametr image - to wskaŸnik na pocz¹tek danych z bitmapy
* parametr threadNumber - to liczba w¹tków, która ma zostaæ u¿yta do wykonania zadania
* funkcja zwraca wynik tj. zwraca czas wykonania siê histogramu
*/

long long runHistogramFunction(HINSTANCE library, Image* image, short threadNumber, int* r, int* g, int* b);

//funkcja runFunctions ma za zadanie wywo³aæ histogram przed rozmyciem, nastêpnie rozmycie obrazu, a na koniec histogram po rozmyciu obrazu

long long runFunctions(System::String^ inputfileName, System::String^ outputfileName, System::String^ numberOfThreads, bool dllType,
	System::Windows::Forms::DataVisualization::Charting::Chart^ chart1, System::Windows::Forms::DataVisualization::Charting::Chart^ chart2);

#endif // !UTILITIES_H

