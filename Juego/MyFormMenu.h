#pragma once
#include "MyForm.h"
#include "MyFormCreditos.h"
#include "MyFormRanking.h"

namespace TrabajoFinal2025 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Resumen de MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();

			//
			//TODO: agregar código de constructor aquí
			//
		}

	protected:
		/// <summary>
		/// Limpiar los recursos que se estén usando.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}

		}
	private: System::Windows::Forms::Button^ START;

	private: System::Windows::Forms::Button^ RANKING;
	private: System::Windows::Forms::Button^ CREDITOS;
	protected:

	protected:

	private:
		/// <summary>
		/// Variable del diseñador necesaria.
		/// </summary>
		System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Método necesario para admitir el Diseñador. No se puede modificar
		/// el contenido de este método con el editor de código.
		/// </summary>
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(MyForm::typeid));
			this->START = (gcnew System::Windows::Forms::Button());
			this->RANKING = (gcnew System::Windows::Forms::Button());
			this->CREDITOS = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// START
			// 
			this->START->BackColor = System::Drawing::Color::Transparent;
			this->START->BackgroundImageLayout = System::Windows::Forms::ImageLayout::None;
			this->START->Cursor = System::Windows::Forms::Cursors::Default;
			this->START->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 11.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->START->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
			this->START->Location = System::Drawing::Point(56, 377);
			this->START->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->START->Name = L"START";
			this->START->Size = System::Drawing::Size(148, 48);
			this->START->TabIndex = 0;
			this->START->Text = L"START";
			this->START->UseVisualStyleBackColor = false;
			this->START->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->START->FlatAppearance->BorderSize = 0;
			this->START->Click += gcnew System::EventHandler(this, &MyForm::START_Click);
			// 
			// RANKING
			// 
			this->RANKING->BackColor = System::Drawing::Color::Transparent;
			this->RANKING->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 11.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->RANKING->ForeColor = System::Drawing::SystemColors::ControlLightLight;
			this->RANKING->Location = System::Drawing::Point(297, 474);
			this->RANKING->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->RANKING->Name = L"RANKING";
			this->RANKING->Size = System::Drawing::Size(148, 49);
			this->RANKING->TabIndex = 2;
			this->RANKING->Text = L"RANKING";
			this->RANKING->UseVisualStyleBackColor = false;
			this->RANKING->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->RANKING->FlatAppearance->BorderSize = 0;
			this->RANKING->Click += gcnew System::EventHandler(this, &MyForm::RANKING_Click);
			// 
			// CREDITOS
			// 
			this->CREDITOS->BackColor = System::Drawing::Color::Transparent;
			this->CREDITOS->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 11.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->CREDITOS->ForeColor = System::Drawing::SystemColors::ControlLightLight;
			this->CREDITOS->Location = System::Drawing::Point(531, 377);
			this->CREDITOS->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->CREDITOS->Name = L"CREDITOS";
			this->CREDITOS->Size = System::Drawing::Size(148, 48);
			this->CREDITOS->TabIndex = 3;
			this->CREDITOS->Text = L"CREDITOS";
			this->CREDITOS->UseVisualStyleBackColor = false;
			this->CREDITOS->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->CREDITOS->FlatAppearance->BorderSize = 0;
			this->CREDITOS->Click += gcnew System::EventHandler(this, &MyForm::CREDITOS_Click);
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackgroundImage = System::Drawing::Image::FromFile("Titulo.png");
			this->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->ClientSize = System::Drawing::Size(735, 571);
			this->Controls->Add(this->CREDITOS);
			this->Controls->Add(this->RANKING);
			this->Controls->Add(this->START);
			this->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->Name = L"MyForm";
			this->Text = L"Menu";
			this->Load += gcnew System::EventHandler(this, &MyForm::MyForm_Load);
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void START_Click(System::Object^ sender, System::EventArgs^ e) {
		MyForm^ juego = gcnew MyForm();
		juego->ShowDialog();
		this->Show();
	}
	private: System::Void CREDITOS_Click(System::Object^ sender, System::EventArgs^ e) {
		MyFormCreditos^ creditos = gcnew MyFormCreditos();
		creditos->ShowDialog();
		this->Show();
	}
	private: System::Void RANKING_Click(System::Object^ sender, System::EventArgs^ e) {
		MyFormRanking^ ranking = gcnew MyFormRanking();
		ranking->ShowDialog();
		this->Show();
	}
	private: System::Void MyForm_Load(System::Object^ sender, System::EventArgs^ e) {
	}
	};
}
