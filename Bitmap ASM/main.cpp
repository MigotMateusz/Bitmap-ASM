/*-------------------------------------------------------------------- -
; ROZMYCIE OBRAZU I HISTOGRAM
; 06.11.2020 Mateusz Migot
; Informatyka SSI semestr 5 rok akademicki 2020 / 2021
; v.0.0.1 - stworzona solucja w visual studio 2019 (13.10.2020)
; v.0.0.2 - stworzony interfejs graficzny oraz wczytywanie i zapisywanie bitmapy(15.10.2020)
; v.0.1 - finalna wersja interfejsu graficznego oraz podstawowe funkcjonalności programu głównego(20.10.2020)
; v.0.2.1 - dodanie CppDLL do projektu i połączenie dynamiczne biblioteki z programem głównym(21.10.2020)
; v.0.2.2 - dodanie ASMDLL do projektu i połączenie dynamiczne biblioteki z programem główny(22.10.2020)
; v.0.2.3 - zaimplementowany algorytm obliczający histogram obrazu(CppDLL) (22.10.2020)
; v.0.2.4 - zaimplementowany algorytm rozmycia obrazu(CppDLL) (24.10.2020)
; v.0.2.5 - dodanie równoległego wykonywania się funkcji(27.10.2020)
; v.0.3 - zaimplementowany algorytm obliczający histogram obrazu(ASMDLL)(wersja 32 - bitowa) (29.10.2020)
; v.0.3.1 - zaimplementowany algorytm rozmycia obrazu(ASMDLL)(wersja 32 - bitowa) (02.11.2020)
; v.0.4 - zmiana projektu funkcji bibliotecznej(ASMDLL) na wersję 64 - bitową(04.11.2020)
; v.0.5 - zmiana funkcji histogramu i funkcji rozmycia obrazu(ASM) na wersje 64 - bitowe(04.11.2020)
; v.0.5 - dodanie operacji wektorowych do histogramu(04.11.2020)
; v.0.6 - finalna wersja funkcji rozmycia obrazu(wykorzystująca operacje wektorowe) (05.11.2020)
; v.1.0 - finalna i aktualna wersja programu z wszystkimi funkcjonalnościami i zabezpieczeniami, zgodna z założeniami(05.11.2020)
; -------------------------------------------------------------------- - */
#include "pch.h"
#include "Form1.h"

int main() {
	System::Windows::Forms::Application::EnableVisualStyles();
	System::Windows::Forms::Application::SetCompatibleTextRenderingDefault(false);
	System::Windows::Forms::Application::Run(gcnew CppCLRWinformsProjekt::Form1());
	return 0;
}