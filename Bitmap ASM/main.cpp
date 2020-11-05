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
#include "Form1.h"


//[STAThread]
int main() {
	System::Windows::Forms::Application::EnableVisualStyles();
	System::Windows::Forms::Application::SetCompatibleTextRenderingDefault(false);
	System::Windows::Forms::Application::Run(gcnew CppCLRWinformsProjekt::Form1());
	return 0;
}