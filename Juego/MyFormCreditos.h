#pragma once

namespace Juego
{
    using namespace System;
    using namespace System::ComponentModel;
    using namespace System::Collections;
    using namespace System::Windows::Forms;
    using namespace System::Data;
    using namespace System::Drawing;

    /// <summary>
    /// Ventana que muestra los créditos del juego
    /// </summary>
    public ref class MyFormCreditos : public System::Windows::Forms::Form
    {
    public:
        MyFormCreditos(void)
        {
            InitializeComponent();
        }

    protected:
        /// <summary>
        /// Liberar los recursos usados.
        /// </summary>
        ~MyFormCreditos()
        {
            if (components)
            {
                delete components;
            }
        }

    private: /* ----------  CONTROLES  ---------- */
        System::Windows::Forms::Label^ lblTitulo;
        System::Windows::Forms::Label^ lblAlumno1;
        System::Windows::Forms::Label^ lblAlumno2;
        System::Windows::Forms::Label^ lblAlumno3;
        System::Windows::Forms::PictureBox^ picAlumno1;
        System::Windows::Forms::PictureBox^ picAlumno2;
        System::Windows::Forms::PictureBox^ picAlumno3;

        System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
        void InitializeComponent(void)
        {
            this->lblTitulo = (gcnew System::Windows::Forms::Label());
            this->lblAlumno1 = (gcnew System::Windows::Forms::Label());
            this->lblAlumno2 = (gcnew System::Windows::Forms::Label());
            this->lblAlumno3 = (gcnew System::Windows::Forms::Label());
            this->picAlumno1 = (gcnew System::Windows::Forms::PictureBox());
            this->picAlumno2 = (gcnew System::Windows::Forms::PictureBox());
            this->picAlumno3 = (gcnew System::Windows::Forms::PictureBox());
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->picAlumno1))->BeginInit();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->picAlumno2))->BeginInit();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->picAlumno3))->BeginInit();
            this->SuspendLayout();
            // 
            // lblTitulo
            // 
            this->lblTitulo->AutoSize = true;
            this->lblTitulo->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F,
                System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
            this->lblTitulo->Location = System::Drawing::Point(305, 11);
            this->lblTitulo->Name = L"lblTitulo";
            this->lblTitulo->Size = System::Drawing::Size(145, 29);
            this->lblTitulo->TabIndex = 0;
            this->lblTitulo->Text = L"CREDITOS";
            // 
            // lblAlumno1
            // 
            this->lblAlumno1->AutoSize = true;
            this->lblAlumno1->Location = System::Drawing::Point(39, 97);
            this->lblAlumno1->Name = L"lblAlumno1";
            this->lblAlumno1->Size = System::Drawing::Size(207, 16);
            this->lblAlumno1->TabIndex = 1;
            this->lblAlumno1->Text = L"Fabrizio Arias Dextre u202420862";
            // 
            // lblAlumno2
            // 
            this->lblAlumno2->AutoSize = true;
            this->lblAlumno2->Location = System::Drawing::Point(449, 97);
            this->lblAlumno2->Name = L"lblAlumno2";
            this->lblAlumno2->Size = System::Drawing::Size(267, 16);
            this->lblAlumno2->TabIndex = 2;
            this->lblAlumno2->Text = L"Eduardo Jesús Osorio Ramírez u202421631";
            // 
            // lblAlumno3
            // 
            this->lblAlumno3->AutoSize = true;
            this->lblAlumno3->Location = System::Drawing::Point(228, 378);
            this->lblAlumno3->Name = L"lblAlumno3";
            this->lblAlumno3->Size = System::Drawing::Size(291, 16);
            this->lblAlumno3->TabIndex = 3;
            this->lblAlumno3->Text = L"Mijail Alexander Matihues Quevedo u202413533";
            // 
            // picAlumno1
            // 
            this->picAlumno1->Location = System::Drawing::Point(55, 137);
            this->picAlumno1->Name = L"picAlumno1";
            this->picAlumno1->Size = System::Drawing::Size(133, 62);
            this->picAlumno1->TabIndex = 4;
            this->picAlumno1->TabStop = false;
            // 
            // picAlumno2
            // 
            this->picAlumno2->Location = System::Drawing::Point(552, 137);
            this->picAlumno2->Name = L"picAlumno2";
            this->picAlumno2->Size = System::Drawing::Size(133, 62);
            this->picAlumno2->TabIndex = 5;
            this->picAlumno2->TabStop = false;
            this->picAlumno2->Click += gcnew System::EventHandler(this, &MyFormCreditos::picAlumno2_Click);
            // 
            // picAlumno3
            // 
            this->picAlumno3->Location = System::Drawing::Point(311, 426);
            this->picAlumno3->Name = L"picAlumno3";
            this->picAlumno3->Size = System::Drawing::Size(133, 62);
            this->picAlumno3->TabIndex = 6;
            this->picAlumno3->TabStop = false;
            // 
            // MyFormCreditos
            // 
            this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
            this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
            this->ClientSize = System::Drawing::Size(751, 646);
            this->Controls->Add(this->picAlumno3);
            this->Controls->Add(this->picAlumno2);
            this->Controls->Add(this->picAlumno1);
            this->Controls->Add(this->lblAlumno3);
            this->Controls->Add(this->lblAlumno2);
            this->Controls->Add(this->lblAlumno1);
            this->Controls->Add(this->lblTitulo);
            this->Name = L"MyFormCreditos";
            this->Text = L"MyFormCreditos";
            this->Load += gcnew System::EventHandler(this, &MyFormCreditos::MyFormCreditos_Load);
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->picAlumno1))->EndInit();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->picAlumno2))->EndInit();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->picAlumno3))->EndInit();
            this->ResumeLayout(false);
            this->PerformLayout();
        }
#pragma endregion

    private:
        /* ----------  EVENTOS  ---------- */
        System::Void picAlumno2_Click(System::Object^ sender, System::EventArgs^ e)
        {
            // Acción opcional al hacer clic en la foto 2
        }

        System::Void MyFormCreditos_Load(System::Object^ sender, System::EventArgs^ e)
        {
            // Código de inicialización adicional si lo necesitas
        }
    };
}
