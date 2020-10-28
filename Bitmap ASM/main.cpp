/*
* Rozmycie obrazu i histogram
* 29.10.2020
* Mateusz Migot
* Informatyka SSI rok 3 sem.5
* v0.2 - dzia³aj¹ce funkcje biblioteczne napisane w jêzyku wysokiego poziomu, skoñczone GUI programu g³ównego
* Zmiany wzglêdem v0.1 - dodana implementacja w¹tków oraz zapis czasu wykonania siê funkcji do pliku
*/
#include "pch.h"
#include "Form1.h"


//[STAThread]
int main() {
	System::Windows::Forms::Application::EnableVisualStyles();
	System::Windows::Forms::Application::SetCompatibleTextRenderingDefault(false);
	System::Windows::Forms::Application::Run(gcnew CppCLRWinformsProjekt::Form1());
	return 0;
}