#pragma once
#include <thread>
#include <String>
#include <fstream>
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

	private: System::Windows::Forms::TextBox^ inputFileNameTextBox;

	private: System::Windows::Forms::ComboBox^ comboBox1;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::Button^ button1;
	private: System::Windows::Forms::Label^ label2;

	private: System::Windows::Forms::Label^ label4;
	private: System::Windows::Forms::TextBox^ outputFileNameTextBox;

	private: System::Windows::Forms::Label^ label5;
	private: System::Windows::Forms::Label^ label6;


	private: System::Windows::Forms::ListView^ listView1;
	private: System::Windows::Forms::Label^ label7;
	private: System::Windows::Forms::Label^ label8;
	private: System::Windows::Forms::Label^ label9;
	private: System::Windows::Forms::DataVisualization::Charting::Chart^ chart1;
	private: System::Windows::Forms::DataVisualization::Charting::Chart^ chart2;

	private:
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code

		void InitializeComponent(void)
		{
			System::Windows::Forms::DataVisualization::Charting::ChartArea^ chartArea1 = (gcnew System::Windows::Forms::DataVisualization::Charting::ChartArea());
			System::Windows::Forms::DataVisualization::Charting::Series^ series1 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			System::Windows::Forms::DataVisualization::Charting::Series^ series2 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			System::Windows::Forms::DataVisualization::Charting::Series^ series3 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			System::Windows::Forms::DataVisualization::Charting::ChartArea^ chartArea2 = (gcnew System::Windows::Forms::DataVisualization::Charting::ChartArea());
			System::Windows::Forms::DataVisualization::Charting::Series^ series4 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			System::Windows::Forms::DataVisualization::Charting::Series^ series5 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			System::Windows::Forms::DataVisualization::Charting::Series^ series6 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			this->cppDllRadioBox = (gcnew System::Windows::Forms::RadioButton());
			this->asmDllRadioBox = (gcnew System::Windows::Forms::RadioButton());
			this->inputFileNameTextBox = (gcnew System::Windows::Forms::TextBox());
			this->comboBox1 = (gcnew System::Windows::Forms::ComboBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->outputFileNameTextBox = (gcnew System::Windows::Forms::TextBox());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->listView1 = (gcnew System::Windows::Forms::ListView());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->label8 = (gcnew System::Windows::Forms::Label());
			this->label9 = (gcnew System::Windows::Forms::Label());
			this->chart1 = (gcnew System::Windows::Forms::DataVisualization::Charting::Chart());
			this->chart2 = (gcnew System::Windows::Forms::DataVisualization::Charting::Chart());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->chart1))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->chart2))->BeginInit();
			this->SuspendLayout();
			// 
			// cppDllRadioBox
			// 
			this->cppDllRadioBox->AutoSize = true;
			this->cppDllRadioBox->Checked = true;
			this->cppDllRadioBox->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10));
			this->cppDllRadioBox->Location = System::Drawing::Point(267, 155);
			this->cppDllRadioBox->Name = L"cppDllRadioBox";
			this->cppDllRadioBox->Size = System::Drawing::Size(71, 21);
			this->cppDllRadioBox->TabIndex = 0;
			this->cppDllRadioBox->TabStop = true;
			this->cppDllRadioBox->Text = L"Cpp Dll";
			this->cppDllRadioBox->UseVisualStyleBackColor = true;
			// 
			// asmDllRadioBox
			// 
			this->asmDllRadioBox->AutoSize = true;
			this->asmDllRadioBox->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10));
			this->asmDllRadioBox->Location = System::Drawing::Point(351, 155);
			this->asmDllRadioBox->Name = L"asmDllRadioBox";
			this->asmDllRadioBox->Size = System::Drawing::Size(75, 21);
			this->asmDllRadioBox->TabIndex = 1;
			this->asmDllRadioBox->Text = L"ASM Dll";
			this->asmDllRadioBox->UseVisualStyleBackColor = true;
			// 
			// inputFileNameTextBox
			// 
			this->inputFileNameTextBox->Location = System::Drawing::Point(250, 41);
			this->inputFileNameTextBox->Name = L"inputFileNameTextBox";
			this->inputFileNameTextBox->Size = System::Drawing::Size(500, 20);
			this->inputFileNameTextBox->TabIndex = 2;
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
			this->comboBox1->Location = System::Drawing::Point(267, 190);
			this->comboBox1->Name = L"comboBox1";
			this->comboBox1->Size = System::Drawing::Size(121, 24);
			this->comboBox1->TabIndex = 3;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10));
			this->label1->Location = System::Drawing::Point(82, 197);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(102, 17);
			this->label1->TabIndex = 4;
			this->label1->Text = L"Liczba w¹tków:";
			// 
			// button1
			// 
			this->button1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(238)));
			this->button1->Location = System::Drawing::Point(604, 194);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(146, 23);
			this->button1->TabIndex = 5;
			this->button1->Text = L"URUCHOM";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &Form1::button1_Click);
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10));
			this->label2->Location = System::Drawing::Point(82, 155);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(179, 17);
			this->label2->TabIndex = 6;
			this->label2->Text = L"Wybór funkcji bibliotecznej:";
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 11, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(238)));
			this->label4->ForeColor = System::Drawing::SystemColors::InactiveCaptionText;
			this->label4->Location = System::Drawing::Point(12, 9);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(313, 18);
			this->label4->TabIndex = 8;
			this->label4->Text = L"Rozmycie obrazu i histogram - Mateusz Migot";
			// 
			// outputFileNameTextBox
			// 
			this->outputFileNameTextBox->Location = System::Drawing::Point(250, 81);
			this->outputFileNameTextBox->Name = L"outputFileNameTextBox";
			this->outputFileNameTextBox->Size = System::Drawing::Size(500, 20);
			this->outputFileNameTextBox->TabIndex = 9;
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(238)));
			this->label5->Location = System::Drawing::Point(82, 43);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(149, 17);
			this->label5->TabIndex = 10;
			this->label5->Text = L"Nazwa wejœciowa pliku";
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(238)));
			this->label6->Location = System::Drawing::Point(82, 84);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(148, 17);
			this->label6->TabIndex = 11;
			this->label6->Text = L"Nazwa wyjœciowa pliku";
			// 
			// listView1
			// 
			this->listView1->Alignment = System::Windows::Forms::ListViewAlignment::Default;
			this->listView1->GridLines = true;
			this->listView1->HideSelection = false;
			this->listView1->Location = System::Drawing::Point(791, 81);
			this->listView1->Name = L"listView1";
			this->listView1->Size = System::Drawing::Size(181, 358);
			this->listView1->TabIndex = 14;
			this->listView1->UseCompatibleStateImageBehavior = false;
			this->listView1->View = System::Windows::Forms::View::List;
			// 
			// label7
			// 
			this->label7->AutoSize = true;
			this->label7->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10));
			this->label7->Location = System::Drawing::Point(839, 44);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(88, 17);
			this->label7->TabIndex = 15;
			this->label7->Text = L"Lista czasów";
			// 
			// label8
			// 
			this->label8->AutoSize = true;
			this->label8->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(238)));
			this->label8->Location = System::Drawing::Point(85, 250);
			this->label8->Name = L"label8";
			this->label8->Size = System::Drawing::Size(175, 16);
			this->label8->TabIndex = 16;
			this->label8->Text = L"Histogram przed rozmyciem";
			// 
			// label9
			// 
			this->label9->AutoSize = true;
			this->label9->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(238)));
			this->label9->Location = System::Drawing::Point(443, 250);
			this->label9->Name = L"label9";
			this->label9->Size = System::Drawing::Size(145, 16);
			this->label9->TabIndex = 17;
			this->label9->Text = L"Histogram po rozmyciu";
			// 
			// chart1
			// 
			chartArea1->AxisX->LabelStyle->Enabled = false;
			chartArea1->AxisY->LabelStyle->Enabled = false;
			chartArea1->Name = L"ChartArea1";
			this->chart1->ChartAreas->Add(chartArea1);
			this->chart1->Location = System::Drawing::Point(85, 269);
			this->chart1->Name = L"chart1";
			this->chart1->Palette = System::Windows::Forms::DataVisualization::Charting::ChartColorPalette::Bright;
			series1->ChartArea = L"ChartArea1";
			series1->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Line;
			series1->Color = System::Drawing::Color::Blue;
			series1->LabelForeColor = System::Drawing::Color::Gray;
			series1->MarkerColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(255)), static_cast<System::Int32>(static_cast<System::Byte>(192)),
				static_cast<System::Int32>(static_cast<System::Byte>(192)));
			series1->Name = L"Blue";
			series2->ChartArea = L"ChartArea1";
			series2->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Line;
			series2->Color = System::Drawing::Color::Lime;
			series2->Name = L"Green";
			series3->ChartArea = L"ChartArea1";
			series3->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Line;
			series3->Color = System::Drawing::Color::Red;
			series3->LabelBorderDashStyle = System::Windows::Forms::DataVisualization::Charting::ChartDashStyle::NotSet;
			series3->Name = L"Red";
			this->chart1->Series->Add(series1);
			this->chart1->Series->Add(series2);
			this->chart1->Series->Add(series3);
			this->chart1->Size = System::Drawing::Size(304, 170);
			this->chart1->TabIndex = 18;
			this->chart1->Text = L"chart1";
			// 
			// chart2
			// 
			chartArea2->AxisX->LabelStyle->Enabled = false;
			chartArea2->AxisY->LabelStyle->Enabled = false;
			chartArea2->Name = L"ChartArea1";
			this->chart2->ChartAreas->Add(chartArea2);
			this->chart2->Location = System::Drawing::Point(446, 269);
			this->chart2->Name = L"chart2";
			this->chart2->Palette = System::Windows::Forms::DataVisualization::Charting::ChartColorPalette::Bright;
			series4->ChartArea = L"ChartArea1";
			series4->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Line;
			series4->Color = System::Drawing::Color::Blue;
			series4->LabelForeColor = System::Drawing::Color::Gray;
			series4->MarkerColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(255)), static_cast<System::Int32>(static_cast<System::Byte>(192)),
				static_cast<System::Int32>(static_cast<System::Byte>(192)));
			series4->Name = L"Blue";
			series5->ChartArea = L"ChartArea1";
			series5->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Line;
			series5->Color = System::Drawing::Color::Lime;
			series5->Name = L"Green";
			series6->ChartArea = L"ChartArea1";
			series6->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Line;
			series6->Color = System::Drawing::Color::Red;
			series6->LabelBorderDashStyle = System::Windows::Forms::DataVisualization::Charting::ChartDashStyle::NotSet;
			series6->Name = L"Red";
			this->chart2->Series->Add(series4);
			this->chart2->Series->Add(series5);
			this->chart2->Series->Add(series6);
			this->chart2->Size = System::Drawing::Size(304, 170);
			this->chart2->TabIndex = 19;
			this->chart2->Text = L"chart2";
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::SystemColors::ControlDark;
			this->ClientSize = System::Drawing::Size(984, 461);
			this->Controls->Add(this->chart2);
			this->Controls->Add(this->chart1);
			this->Controls->Add(this->label9);
			this->Controls->Add(this->label8);
			this->Controls->Add(this->label7);
			this->Controls->Add(this->listView1);
			this->Controls->Add(this->label6);
			this->Controls->Add(this->label5);
			this->Controls->Add(this->outputFileNameTextBox);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->comboBox1);
			this->Controls->Add(this->inputFileNameTextBox);
			this->Controls->Add(this->asmDllRadioBox);
			this->Controls->Add(this->cppDllRadioBox);
			this->MaximizeBox = false;
			this->MaximumSize = System::Drawing::Size(1000, 1000);
			this->MinimumSize = System::Drawing::Size(599, 232);
			this->Name = L"Form1";
			this->ShowIcon = false;
			this->Text = L"Bitmap ASM";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->chart1))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->chart2))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();
			readLogFile(this->listView1);
		}
#pragma endregion

	private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
		String^ inputfileName = this->inputFileNameTextBox->Text;
		String^ outputfileName = this->outputFileNameTextBox->Text;
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
			addToLogFile(this->listView1, std::to_string(timeElapsed));
		}
	}
};
}

