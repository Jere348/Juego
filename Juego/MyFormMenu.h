#pragma once
#include "MyForm.h"
#include "MyFormCreditos.h"
#include "MyFormRanking.h"

namespace Juego {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	public ref class MyFormMenu : public System::Windows::Forms::Form
	{
	public:
		MyFormMenu(void)
		{
			InitializeComponent();
		}

	protected:
		~MyFormMenu()
		{
			if (components)
			{
				delete components;
			}
		}

	private:
		System::Windows::Forms::Button^ START;
		System::Windows::Forms::Button^ RANKING;
		System::Windows::Forms::Button^ CREDITOS;

		System::ComponentModel::Container^ components;
				
#pragma region Windows Form Designer generated code
		void InitializeComponent(void)
		{
			this->START = (gcnew System::Windows::Forms::Button());
			this->RANKING = (gcnew System::Windows::Forms::Button());
			this->CREDITOS = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// START
			// 
			this->START->BackColor = System::Drawing::Color::Transparent;
			this->START->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->START->FlatAppearance->BorderSize = 0;
			this->START->FlatAppearance->MouseDownBackColor = System::Drawing::Color::Transparent;	
			this->START->FlatAppearance->MouseOverBackColor = System::Drawing::Color::Transparent;
			this->START->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 11.25F, System::Drawing::FontStyle::Bold));
			this->START->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
			this->START->Location = System::Drawing::Point(56, 377);
			this->START->Name = L"START";
			this->START->Size = System::Drawing::Size(148, 48);
			this->START->TabIndex = 0;
			this->START->Text = L"START";
			this->START->UseVisualStyleBackColor = false;
			this->START->Click += gcnew System::EventHandler(this, &MyFormMenu::START_Click);
			// 
			// RANKING
			// 
			this->RANKING->BackColor = System::Drawing::Color::Transparent;
			this->RANKING->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->RANKING->FlatAppearance->BorderSize = 0;
			this->RANKING->FlatAppearance->MouseDownBackColor = System::Drawing::Color::Transparent;
			this->RANKING->FlatAppearance->MouseOverBackColor = System::Drawing::Color::Transparent;
			this->RANKING->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 11.25F, System::Drawing::FontStyle::Bold));
			this->RANKING->ForeColor = System::Drawing::SystemColors::ControlLightLight;
			this->RANKING->Location = System::Drawing::Point(297, 474);
			this->RANKING->Name = L"RANKING";
			this->RANKING->Size = System::Drawing::Size(148, 49);
			this->RANKING->TabIndex = 2;
			this->RANKING->Text = L"RANKING";
			this->RANKING->UseVisualStyleBackColor = false;
			this->RANKING->Click += gcnew System::EventHandler(this, &MyFormMenu::RANKING_Click);
			// 
			// CREDITOS
			// 
			this->CREDITOS->BackColor = System::Drawing::Color::Transparent;
			this->CREDITOS->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->CREDITOS->FlatAppearance->BorderSize = 0;
			this->CREDITOS->FlatAppearance->MouseDownBackColor = System::Drawing::Color::Transparent;
			this->CREDITOS->FlatAppearance->MouseOverBackColor = System::Drawing::Color::Transparent;
			this->CREDITOS->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 11.25F, System::Drawing::FontStyle::Bold));
			this->CREDITOS->ForeColor = System::Drawing::SystemColors::ControlLightLight;
			this->CREDITOS->Location = System::Drawing::Point(531, 377);
			this->CREDITOS->Name = L"CREDITOS";
			this->CREDITOS->Size = System::Drawing::Size(148, 48);
			this->CREDITOS->TabIndex = 3;
			this->CREDITOS->Text = L"CREDITOS";
			this->CREDITOS->UseVisualStyleBackColor = false;
			this->CREDITOS->Click += gcnew System::EventHandler(this, &MyFormMenu::CREDITOS_Click);
			// 
			// MyFormMenu
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackgroundImage = System::Drawing::Image::FromFile("Titulo.png");
			this->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->ClientSize = System::Drawing::Size(735, 571);
			this->Controls->Add(this->CREDITOS);
			this->Controls->Add(this->RANKING);
			this->Controls->Add(this->START);
			this->Name = L"MyFormMenu";
			this->Text = L"Menu";
			this->Load += gcnew System::EventHandler(this, &MyFormMenu::MyFormMenu_Load);
			this->ResumeLayout(false);
		}
#pragma endregion

	private:
		System::Void START_Click(System::Object^ sender, System::EventArgs^ e) {
			MyFormJuego^ juego = gcnew MyFormJuego();
			juego->ShowDialog();
			this->Show();
		}

		System::Void RANKING_Click(System::Object^ sender, System::EventArgs^ e) {
			MyFormRanking^ ranking = gcnew MyFormRanking();
			ranking->ShowDialog();
			this->Show();
		}

		System::Void CREDITOS_Click(System::Object^ sender, System::EventArgs^ e) {
			MyFormCreditos^ creditos = gcnew MyFormCreditos();
			creditos->ShowDialog();
			this->Show();
		}

		System::Void MyFormMenu_Load(System::Object^ sender, System::EventArgs^ e) {
			// Código de carga opcional
		}
	};
}
