/*
* Rozmycie obrazu i histogram
* 29.10.2020
* Mateusz Migot
* Informatyka SSI rok 3 sem.5
* v0.2 - dzia�aj�ce funkcje biblioteczne napisane w j�zyku wysokiego poziomu, sko�czone GUI programu g��wnego
* Zmiany wzgl�dem v0.1 - dodana implementacja w�tk�w oraz zapis czasu wykonania si� funkcji do pliku
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