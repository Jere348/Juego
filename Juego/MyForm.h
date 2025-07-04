#pragma once
#include "Juego.h"

namespace MyForm {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			InicializarJuego();
		}

	protected:
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}

	private:
		System::ComponentModel::Container^ components;
		Juego^ juego;
		PictureBox^ pbJugador;
		Timer^ timerJuego;

#pragma region Windows Form Designer generated code
		void InitializeComponent(void)
		{
			this->components = gcnew System::ComponentModel::Container();
			this->Size = System::Drawing::Size(800, 600);
			this->Text = L"Vigilante del Equilibrio";
			this->Padding = System::Windows::Forms::Padding(0);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->KeyPreview = true;
			this->BackColor = System::Drawing::Color::Black;

			this->Load += gcnew System::EventHandler(this, &MyForm::MyForm_Load);
			this->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &MyForm::Form1_KeyDown);
		}
#pragma endregion

	private:
		void InicializarJuego()
		{
			juego = gcnew Juego();

			// Crear PictureBox del jugador
			pbJugador = gcnew PictureBox();
			pbJugador->Size = Drawing::Size(48, 48);
			pbJugador->Location = Point(juego->Jugador->PosicionX, juego->Jugador->PosicionY);
			pbJugador->Image = juego->Jugador->ObtenerSpriteActual();
			pbJugador->SizeMode = PictureBoxSizeMode::StretchImage;
			this->Controls->Add(pbJugador);

			// Asignar fondo del mundo actual
			this->BackgroundImage = juego->ObtenerMundoActual()->Background;
			this->BackgroundImageLayout = ImageLayout::Stretch;

			// Iniciar Timer del juego
			timerJuego = gcnew Timer();
			timerJuego->Interval = 100; // 100 ms por frame
			timerJuego->Tick += gcnew EventHandler(this, &MyForm::ActualizarJuego);
			timerJuego->Start();
		}

		void ActualizarJuego(Object^ sender, EventArgs^ e)
		{
			juego->ActualizarEstado();

			// Actualizar sprite y posición del jugador
			pbJugador->Location = Point(juego->Jugador->PosicionX, juego->Jugador->PosicionY);
			pbJugador->Image = juego->Jugador->ObtenerSpriteActual();

			// Actualizar título con información del estado
			this->Text = "Vidas: " + juego->Jugador->Vidas.ToString() + " | Tiempo: " + juego->TiempoRestante.ToString();

			// Condiciones de fin de juego
			if (juego->JuegoTerminado)
			{
				timerJuego->Stop();
				MessageBox::Show("¡PERDISTE!", "Fin del juego");
			}
			if (juego->VerificarVictoria())
			{
				timerJuego->Stop();
				MessageBox::Show("¡GANASTE!", "Victoria");
			}
		}

		void Form1_KeyDown(Object^ sender, KeyEventArgs^ e)
		{
			if (e->KeyCode == Keys::Left)
				juego->Jugador->Mover("izquierda");
			else if (e->KeyCode == Keys::Right)
				juego->Jugador->Mover("derecha");
			else if (e->KeyCode == Keys::Up)
				juego->Jugador->Mover("arriba");
			else if (e->KeyCode == Keys::Down)
				juego->Jugador->Mover("abajo");
		}

		void MyForm_Load(System::Object^ sender, System::EventArgs^ e) {
			// Opcional: mostrar mensaje inicial o título
		}
	};
}
