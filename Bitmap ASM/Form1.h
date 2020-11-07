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
#pragma once
#include <thread>
#include <String>
#include <fstream>
#include <iostream>
#include "utilities.h"


namespace CppCLRWinformsProjekt {
	
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	//using namespace msclr::interop;
	public ref class Form1 : public System::Windows::Forms::Form
	{
	public:
		Form1(void)
		{
			InitializeComponent();
		}

	protected:
		~Form1()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::RadioButton^ cppDllRadioBox;
	private: System::Windows::Forms::RadioButton^ asmDllRadioBox;
	protected:

	protected:



	private: System::Windows::Forms::ComboBox^ comboBox1;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::Button^ button1;
	private: System::Windows::Forms::Label^ label2;

	private: System::Windows::Forms::Label^ label4;






	private: System::Windows::Forms::ListView^ listView1;
	private: System::Windows::Forms::Label^ label7;
	private: System::Windows::Forms::Label^ label8;
	private: System::Windows::Forms::Label^ label9;
	private: System::Windows::Forms::DataVisualization::Charting::Chart^ chart1;
	private: System::Windows::Forms::DataVisualization::Charting::Chart^ chart2;
	private: System::Windows::Forms::Button^ loadButton;


	private: System::Windows::Forms::Label^ label3;
	private: System::Windows::Forms::Label^ label10;
	private: System::Windows::Forms::Button^ saveButton;




	private:
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code

		void InitializeComponent(void)
		{
			System::Windows::Forms::DataVisualization::Charting::ChartArea^ chartArea3 = (gcnew System::Windows::Forms::DataVisualization::Charting::ChartArea());
			System::Windows::Forms::DataVisualization::Charting::Series^ series7 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			System::Windows::Forms::DataVisualization::Charting::Series^ series8 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			System::Windows::Forms::DataVisualization::Charting::Series^ series9 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			System::Windows::Forms::DataVisualization::Charting::ChartArea^ chartArea4 = (gcnew System::Windows::Forms::DataVisualization::Charting::ChartArea());
			System::Windows::Forms::DataVisualization::Charting::Series^ series10 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			System::Windows::Forms::DataVisualization::Charting::Series^ series11 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			System::Windows::Forms::DataVisualization::Charting::Series^ series12 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			this->cppDllRadioBox = (gcnew System::Windows::Forms::RadioButton());
			this->asmDllRadioBox = (gcnew System::Windows::Forms::RadioButton());
			this->comboBox1 = (gcnew System::Windows::Forms::ComboBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->listView1 = (gcnew System::Windows::Forms::ListView());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->label8 = (gcnew System::Windows::Forms::Label());
			this->label9 = (gcnew System::Windows::Forms::Label());
			this->chart1 = (gcnew System::Windows::Forms::DataVisualization::Charting::Chart());
			this->chart2 = (gcnew System::Windows::Forms::DataVisualization::Charting::Chart());
			this->loadButton = (gcnew System::Windows::Forms::Button());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label10 = (gcnew System::Windows::Forms::Label());
			this->saveButton = (gcnew System::Windows::Forms::Button());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->chart1))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->chart2))->BeginInit();
			this->SuspendLayout();
			// 
			// cppDllRadioBox
			// 
			this->cppDllRadioBox->AutoSize = true;
			this->cppDllRadioBox->Checked = true;
			this->cppDllRadioBox->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10));
			this->cppDllRadioBox->Location = System::Drawing::Point(356, 191);
			this->cppDllRadioBox->Margin = System::Windows::Forms::Padding(4);
			this->cppDllRadioBox->Name = L"cppDllRadioBox";
			this->cppDllRadioBox->Size = System::Drawing::Size(86, 24);
			this->cppDllRadioBox->TabIndex = 0;
			this->cppDllRadioBox->TabStop = true;
			this->cppDllRadioBox->Text = L"Cpp Dll";
			this->cppDllRadioBox->UseVisualStyleBackColor = true;
			// 
			// asmDllRadioBox
			// 
			this->asmDllRadioBox->AutoSize = true;
			this->asmDllRadioBox->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10));
			this->asmDllRadioBox->Location = System::Drawing::Point(468, 191);
			this->asmDllRadioBox->Margin = System::Windows::Forms::Padding(4);
			this->asmDllRadioBox->Name = L"asmDllRadioBox";
			this->asmDllRadioBox->Size = System::Drawing::Size(92, 24);
			this->asmDllRadioBox->TabIndex = 1;
			this->asmDllRadioBox->Text = L"ASM Dll";
			this->asmDllRadioBox->UseVisualStyleBackColor = true;
			// 
			// comboBox1
			// 
			this->comboBox1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(238)));
			this->comboBox1->FormattingEnabled = true;
			this->comboBox1->Items->AddRange(gcnew cli::array< System::Object^  >(64) {
				L"1", L"2", L"3", L"4", L"5", L"6", L"7", L"8",
					L"9", L"10", L"11", L"12", L"13", L"14", L"15", L"16", L"17", L"18", L"19", L"20", L"21", L"22", L"23", L"24", L"25", L"26",
					L"27", L"28", L"29", L"30", L"31", L"32", L"33", L"34", L"35", L"36", L"37", L"38", L"39", L"40", L"41", L"42", L"43", L"44",
					L"45", L"46", L"47", L"48", L"49", L"50", L"51", L"52", L"53", L"54", L"55", L"56", L"57", L"58", L"59", L"60", L"61", L"62",
					L"63", L"64"
			});
			this->comboBox1->Location = System::Drawing::Point(356, 234);
			this->comboBox1->Margin = System::Windows::Forms::Padding(4);
			this->comboBox1->Name = L"comboBox1";
			this->comboBox1->Size = System::Drawing::Size(160, 28);
			this->comboBox1->TabIndex = 3;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10));
			this->label1->Location = System::Drawing::Point(109, 242);
			this->label1->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(124, 20);
			this->label1->TabIndex = 4;
			this->label1->Text = L"Liczba w¹tków:";
			// 
			// button1
			// 
			this->button1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(238)));
			this->button1->Location = System::Drawing::Point(805, 239);
			this->button1->Margin = System::Windows::Forms::Padding(4);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(195, 28);
			this->button1->TabIndex = 5;
			this->button1->Text = L"URUCHOM";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &Form1::button1_Click);
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10));
			this->label2->Location = System::Drawing::Point(109, 191);
			this->label2->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(213, 20);
			this->label2->TabIndex = 6;
			this->label2->Text = L"Wybór funkcji bibliotecznej:";
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 11, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(238)));
			this->label4->ForeColor = System::Drawing::SystemColors::InactiveCaptionText;
			this->label4->Location = System::Drawing::Point(16, 11);
			this->label4->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(389, 24);
			this->label4->TabIndex = 8;
			this->label4->Text = L"Rozmycie obrazu i histogram - Mateusz Migot";
			// 
			// listView1
			// 
			this->listView1->Alignment = System::Windows::Forms::ListViewAlignment::Default;
			this->listView1->GridLines = true;
			this->listView1->HideSelection = false;
			this->listView1->Location = System::Drawing::Point(1055, 100);
			this->listView1->Margin = System::Windows::Forms::Padding(4);
			this->listView1->Name = L"listView1";
			this->listView1->Size = System::Drawing::Size(240, 440);
			this->listView1->TabIndex = 14;
			this->listView1->UseCompatibleStateImageBehavior = false;
			this->listView1->View = System::Windows::Forms::View::List;
			// 
			// label7
			// 
			this->label7->AutoSize = true;
			this->label7->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10));
			this->label7->Location = System::Drawing::Point(1119, 54);
			this->label7->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(108, 20);
			this->label7->TabIndex = 15;
			this->label7->Text = L"Lista czasów";
			// 
			// label8
			// 
			this->label8->AutoSize = true;
			this->label8->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(238)));
			this->label8->Location = System::Drawing::Point(113, 308);
			this->label8->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label8->Name = L"label8";
			this->label8->Size = System::Drawing::Size(221, 20);
			this->label8->TabIndex = 16;
			this->label8->Text = L"Histogram przed rozmyciem";
			// 
			// label9
			// 
			this->label9->AutoSize = true;
			this->label9->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(238)));
			this->label9->Location = System::Drawing::Point(591, 308);
			this->label9->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label9->Name = L"label9";
			this->label9->Size = System::Drawing::Size(183, 20);
			this->label9->TabIndex = 17;
			this->label9->Text = L"Histogram po rozmyciu";
			// 
			// chart1
			// 
			chartArea3->AxisX->LabelStyle->Enabled = false;
			chartArea3->AxisY->LabelStyle->Enabled = false;
			chartArea3->Name = L"ChartArea1";
			this->chart1->ChartAreas->Add(chartArea3);
			this->chart1->Location = System::Drawing::Point(117, 332);
			this->chart1->Margin = System::Windows::Forms::Padding(4);
			this->chart1->Name = L"chart1";
			this->chart1->Palette = System::Windows::Forms::DataVisualization::Charting::ChartColorPalette::Bright;
			series7->ChartArea = L"ChartArea1";
			series7->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Line;
			series7->Color = System::Drawing::Color::Blue;
			series7->LabelForeColor = System::Drawing::Color::Gray;
			series7->MarkerColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(255)), static_cast<System::Int32>(static_cast<System::Byte>(192)),
				static_cast<System::Int32>(static_cast<System::Byte>(192)));
			series7->Name = L"Blue";
			series8->ChartArea = L"ChartArea1";
			series8->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Line;
			series8->Color = System::Drawing::Color::Lime;
			series8->Name = L"Green";
			series9->ChartArea = L"ChartArea1";
			series9->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Line;
			series9->Color = System::Drawing::Color::Red;
			series9->LabelBorderDashStyle = System::Windows::Forms::DataVisualization::Charting::ChartDashStyle::NotSet;
			series9->Name = L"Red";
			this->chart1->Series->Add(series7);
			this->chart1->Series->Add(series8);
			this->chart1->Series->Add(series9);
			this->chart1->Size = System::Drawing::Size(405, 209);
			this->chart1->TabIndex = 18;
			this->chart1->Text = L"chart1";
			// 
			// chart2
			// 
			chartArea4->AxisX->LabelStyle->Enabled = false;
			chartArea4->AxisY->LabelStyle->Enabled = false;
			chartArea4->Name = L"ChartArea1";
			this->chart2->ChartAreas->Add(chartArea4);
			this->chart2->Location = System::Drawing::Point(595, 331);
			this->chart2->Margin = System::Windows::Forms::Padding(4);
			this->chart2->Name = L"chart2";
			this->chart2->Palette = System::Windows::Forms::DataVisualization::Charting::ChartColorPalette::Bright;
			series10->ChartArea = L"ChartArea1";
			series10->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Line;
			series10->Color = System::Drawing::Color::Blue;
			series10->LabelForeColor = System::Drawing::Color::Gray;
			series10->MarkerColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(255)), static_cast<System::Int32>(static_cast<System::Byte>(192)),
				static_cast<System::Int32>(static_cast<System::Byte>(192)));
			series10->Name = L"Blue";
			series11->ChartArea = L"ChartArea1";
			series11->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Line;
			series11->Color = System::Drawing::Color::Lime;
			series11->Name = L"Green";
			series12->ChartArea = L"ChartArea1";
			series12->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Line;
			series12->Color = System::Drawing::Color::Red;
			series12->LabelBorderDashStyle = System::Windows::Forms::DataVisualization::Charting::ChartDashStyle::NotSet;
			series12->Name = L"Red";
			this->chart2->Series->Add(series10);
			this->chart2->Series->Add(series11);
			this->chart2->Series->Add(series12);
			this->chart2->Size = System::Drawing::Size(405, 209);
			this->chart2->TabIndex = 19;
			this->chart2->Text = L"chart2";
			// 
			// loadButton
			// 
			this->loadButton->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(238)));
			this->loadButton->Location = System::Drawing::Point(113, 70);
			this->loadButton->Name = L"loadButton";
			this->loadButton->Size = System::Drawing::Size(184, 45);
			this->loadButton->TabIndex = 21;
			this->loadButton->Text = L"Za³aduj bitmapê";
			this->loadButton->UseVisualStyleBackColor = true;
			this->loadButton->Click += gcnew System::EventHandler(this, &Form1::loadBitmap);
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(238)));
			this->label3->Location = System::Drawing::Point(314, 84);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(0, 20);
			this->label3->TabIndex = 22;
			// 
			// label10
			// 
			this->label10->AutoSize = true;
			this->label10->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(238)));
			this->label10->Location = System::Drawing::Point(314, 136);
			this->label10->Name = L"label10";
			this->label10->Size = System::Drawing::Size(0, 20);
			this->label10->TabIndex = 24;
			// 
			// saveButton
			// 
			this->saveButton->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(238)));
			this->saveButton->Location = System::Drawing::Point(113, 121);
			this->saveButton->Name = L"saveButton";
			this->saveButton->Size = System::Drawing::Size(184, 46);
			this->saveButton->TabIndex = 23;
			this->saveButton->Text = L"Zapisz bitmapê";
			this->saveButton->UseVisualStyleBackColor = true;
			this->saveButton->Click += gcnew System::EventHandler(this, &Form1::saveBitmap);
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::SystemColors::ControlDark;
			this->ClientSize = System::Drawing::Size(1309, 567);
			this->Controls->Add(this->label10);
			this->Controls->Add(this->saveButton);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->loadButton);
			this->Controls->Add(this->chart2);
			this->Controls->Add(this->chart1);
			this->Controls->Add(this->label9);
			this->Controls->Add(this->label8);
			this->Controls->Add(this->label7);
			this->Controls->Add(this->listView1);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->comboBox1);
			this->Controls->Add(this->asmDllRadioBox);
			this->Controls->Add(this->cppDllRadioBox);
			this->Margin = System::Windows::Forms::Padding(4);
			this->MaximizeBox = false;
			this->MaximumSize = System::Drawing::Size(1327, 1220);
			this->MinimumSize = System::Drawing::Size(793, 275);
			this->Name = L"Form1";
			this->ShowIcon = false;
			this->Text = L"Bitmap ASM";
			this->comboBox1->Text = std::thread::hardware_concurrency().ToString();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->chart1))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->chart2))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();
			readLogFile(this->listView1);
		}
#pragma endregion

	private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
		String^ inputfileName = this->label3->Text;
		String^ outputfileName = this->label10->Text;
		String^ nThreads = this->comboBox1->Text;
		bool isCppDllChecked;
		if (this->cppDllRadioBox->Checked == true)
			isCppDllChecked = true;
		else
			isCppDllChecked = false;
		if (validateStartingParameters(inputfileName, outputfileName, nThreads)) {
			int timeElapsed = runFunctions(inputfileName, outputfileName, nThreads, isCppDllChecked, this->chart1, this->chart2);
			System::Windows::Forms::MessageBox::Show("Operacja zakoñczy³a siê poprawnie.", "Operacja zakoñczona",
				System::Windows::Forms::MessageBoxButtons::OK);
			addToLogFile(this->listView1, std::to_string(timeElapsed),isCppDllChecked, nThreads);
		}
	}

	private: System::Void loadBitmap(System::Object^ sender, System::EventArgs^ e) {
		System::Windows::Forms::OpenFileDialog^ openDialog = gcnew OpenFileDialog;
		openDialog->Filter = "Bitmap(*.bmp)|*.bmp";
		openDialog->RestoreDirectory = true;
		openDialog->ShowHelp = true;
		if (openDialog->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
			if (openDialog->FileName != nullptr) {
				this->label3->Text = openDialog->FileName;
			}
		}
	}
	private: System::Void saveBitmap(System::Object^ sender, System::EventArgs^ e) {
		System::Windows::Forms::SaveFileDialog^ saveDialog = gcnew SaveFileDialog;
		saveDialog->Filter = "Bitmap(*.bmp)|*.bmp";
		saveDialog->RestoreDirectory = true;
		saveDialog->ShowHelp = true;
		if (saveDialog->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
			if (saveDialog->FileName != nullptr) {
				this->label10->Text = saveDialog->FileName;
			}
		}
	}

};
}

