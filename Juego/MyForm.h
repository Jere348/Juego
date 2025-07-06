#pragma once
#include "Juego.h"
#include "Configuracion.h"
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
			this->SetStyle(ControlStyles::AllPaintingInWmPaint |
				ControlStyles::UserPaint |
				ControlStyles::OptimizedDoubleBuffer, true);

			this->UpdateStyles();
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
		bool teclaIzquierda = false;
		bool teclaDerecha = false;
		bool teclaArriba = false;
		bool teclaAbajo = false;
		int framesInvulnerable = 0;


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
			this->KeyUp += gcnew KeyEventHandler(this, &MyForm::Form1_KeyUp);
			this->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &MyForm::Form1_KeyDown);
		}
#pragma endregion

	private:
		void InicializarJuego()
		{
			int anchoMapa = this->ClientSize.Width;
			int altoMapa = this->ClientSize.Height;
			Configuracion::CargarParametrosDesdeArchivo("Parameters.txt");
			juego = gcnew Juego(anchoMapa, altoMapa);

			// Crear PictureBox del jugador
			this->SetStyle(ControlStyles::SupportsTransparentBackColor, true);
			this->BackColor = Color::Transparent;

			pbJugador = gcnew PictureBox();
			pbJugador->Size = Drawing::Size(48, 48);
			pbJugador->Location = Point(juego->Jugador->PosicionX, juego->Jugador->PosicionY);
			pbJugador->Image = juego->Jugador->ObtenerSpriteActual();
			pbJugador->SizeMode = PictureBoxSizeMode::StretchImage;
			this->Controls->Add(pbJugador);
			pbJugador->BringToFront();

			this->BackgroundImage = juego->ObtenerMundoActual()->Background;
			this->BackgroundImageLayout = ImageLayout::Stretch;

			timerJuego = gcnew Timer();
			timerJuego->Interval = 100;
			timerJuego->Tick += gcnew EventHandler(this, &MyForm::ActualizarJuego);
			timerJuego->Start();
		}

		void ActualizarJuego(Object^ sender, EventArgs^ e)
		{
			int ancho = this->ClientSize.Width;
			int alto = this->ClientSize.Height;

			if (teclaIzquierda) juego->Jugador->Mover("izquierda", ancho, alto);
			if (teclaDerecha)  juego->Jugador->Mover("derecha", ancho, alto);
			if (teclaArriba)   juego->Jugador->Mover("arriba", ancho, alto);
			if (teclaAbajo)    juego->Jugador->Mover("abajo", ancho, alto);


			// Redibujar sprite y actualizar posición del PictureBox
			pbJugador->Location = Point(juego->Jugador->PosicionX, juego->Jugador->PosicionY);
			pbJugador->Image = juego->Jugador->ObtenerSpriteActual();

			int anchoMapa = this->ClientSize.Width;
			juego->MoverEnemigosDelMundoActual(anchoMapa);

			// Redibujar enemigos
			for each (Control ^ c in this->Controls) {
				PictureBox^ pb = dynamic_cast<PictureBox^>(c);
				if (pb != nullptr) {
					Enemigo^ enemigo = dynamic_cast<Enemigo^>(pb->Tag);
					if (enemigo != nullptr) {
						pb->Location = Point(enemigo->PosicionX, enemigo->PosicionY);
						pb->Image = enemigo->ObtenerSpriteActual(); //  Cambia de frame
					}
				}
			}

			this->Text = "Vidas: " + juego->Jugador->Vidas.ToString() + " | Tiempo: " + juego->TiempoRestante.ToString();

			if (juego->JuegoTerminado) {
				timerJuego->Stop();
				MessageBox::Show("¡PERDISTE!", "Fin del juego");
			}

			if (juego->VerificarVictoria()) {
				timerJuego->Stop();
				MessageBox::Show("¡GANASTE!", "Victoria");
			}

			for each (Control ^ c in this->Controls) {
				PictureBox^ pb = dynamic_cast<PictureBox^>(c);
				if (pb != nullptr) {
					Enemigo^ enemigo = dynamic_cast<Enemigo^>(pb->Tag);
					if (enemigo != nullptr) {
						pb->Location = Point(enemigo->PosicionX, enemigo->PosicionY);
						pb->Image = enemigo->ObtenerSpriteActual();

						// Colisión con el jugador
						if (pb->Bounds.IntersectsWith(pbJugador->Bounds)) {
							juego->Jugador->PerderVida();

							

							// Mover al jugador al mundo vacío (índice 2)
							CambiarMundo(2);

							
							MessageBox::Show("¡Has sido atacado! Vida -1", "¡Cuidado!", MessageBoxButtons::OK, MessageBoxIcon::Warning);

							// Opcional: mover al jugador a posición inicial segura
							juego->Jugador->PosicionX = 100;
							juego->Jugador->PosicionY = 100;
							pbJugador->Location = Point(100, 100);

							break; // evita múltiples colisiones en el mismo frame
						}
					}
				}
			}

			if (juego->Jugador->Vidas <= 0) {
				timerJuego->Stop();
				MessageBox::Show("¡Te has quedado sin vidas!", "Fin del juego");
				juego->JuegoTerminado = true;
			}
			if (juego->VerificarVictoriaPorEquilibrio()) {
				timerJuego->Stop();
				MessageBox::Show("¡Ganaste! Lograste el equilibrio en el Mundo Blanco.", "Victoria");
				juego->JuegoTerminado = true;
			}
			juego->ActualizarEstado(anchoMapa);

		}


		void Form1_KeyDown(Object^ sender, KeyEventArgs^ e)
		{
			// Activar banderas de movimiento
			if (e->KeyCode == Keys::Left)  teclaIzquierda = true;
			if (e->KeyCode == Keys::Right) teclaDerecha = true;
			if (e->KeyCode == Keys::Up)    teclaArriba = true;
			if (e->KeyCode == Keys::Down)  teclaAbajo = true;

			// CAMBIO DE MUNDO
			if (e->KeyCode == Keys::D1)
				CambiarMundo(0);  // Mundo 1
			else if (e->KeyCode == Keys::D2)
				CambiarMundo(1);  // Mundo 2
			else if (e->KeyCode == Keys::D3)
				CambiarMundo(2);  // Mundo 3

			if (e->KeyCode == Keys::E) {
				for each (Control ^ c in this->Controls) {
					PictureBox^ pb = dynamic_cast<PictureBox^>(c);
					if (pb != nullptr && pb != pbJugador) {
						Recurso^ recurso = dynamic_cast<Recurso^>(pb->Tag);
						if (recurso != nullptr && pbJugador->Bounds.IntersectsWith(pb->Bounds)) {
							juego->Jugador->Recolectar(recurso);
							this->Controls->Remove(pb);
							juego->ObtenerMundoActual()->Recursos->Remove(recurso);
							break;
						}
					}
				}
			}
			if (e->KeyCode == Keys::E) {
				for each (Control ^ c in this->Controls) {
					PictureBox^ pb = dynamic_cast<PictureBox^>(c);
					if (pb != nullptr) {
						Aliado^ aliado = dynamic_cast<Aliado^>(pb->Tag);
						if (aliado != nullptr &&
							pb->Bounds.IntersectsWith(pbJugador->Bounds)) {

							aliado->Ayudar(juego->Jugador);
							MessageBox::Show("Aliado te ha ayudado. +1 Vida", "Gracias", MessageBoxButtons::OK, MessageBoxIcon::Information);
						}
					}
				}
			}
			if (e->KeyCode == Keys::E && juego->ObtenerMundoActual() == juego->Mundos[2]) {
				Recurso^ recursoColocado = juego->Jugador->ColocarRecurso();
				if (recursoColocado != nullptr) {
					// Asignar posición al recurso según el jugador
					recursoColocado->PosicionX = juego->Jugador->PosicionX;
					recursoColocado->PosicionY = juego->Jugador->PosicionY;

					// Agregar a la lista de recursos del Mundo 3
					juego->ObtenerMundoActual()->Recursos->Add(recursoColocado);

					// Crear PictureBox visual
					PictureBox^ pb = gcnew PictureBox();
					pb->Size = Drawing::Size(32, 32);
					pb->Location = Point(recursoColocado->PosicionX, recursoColocado->PosicionY);
					pb->Image = recursoColocado->ObtenerSpriteActual();
					pb->SizeMode = PictureBoxSizeMode::StretchImage;
					pb->BackColor = Color::Transparent;
					pb->Tag = recursoColocado;
					this->Controls->Add(pb);

					pb->BringToFront();
					pbJugador->BringToFront(); // mantener el jugador al frente
				}
			}
		}
		void Form1_KeyUp(Object^ sender, KeyEventArgs^ e)
		{
			if (e->KeyCode == Keys::Left)  teclaIzquierda = false;
			if (e->KeyCode == Keys::Right) teclaDerecha = false;
			if (e->KeyCode == Keys::Up)    teclaArriba = false;
			if (e->KeyCode == Keys::Down)  teclaAbajo = false;
		}


		void MyForm_Load(System::Object^ sender, System::EventArgs^ e) {
			// Opcional: mostrar mensaje inicial o título
		}

		void CambiarMundo(int nuevoIndice)
		{
			// Cambiar en la lógica
			juego->CambiarMundo(nuevoIndice);

			// Cambiar fondo
			this->BackgroundImage = juego->ObtenerMundoActual()->Background;

			List<Control^>^ paraEliminar = gcnew List<Control^>();

			for each (Control ^ c in this->Controls) {
				PictureBox^ pb = dynamic_cast<PictureBox^>(c);
				if (pb != nullptr && pb != pbJugador) {
					paraEliminar->Add(pb);
				}
			}

			for each (Control ^ pb in paraEliminar) {
				this->Controls->Remove(pb);
			}


			// Mostrar los recursos del nuevo mundo
			for each (Recurso ^ r in juego->ObtenerMundoActual()->Recursos) {
				PictureBox^ pb = gcnew PictureBox();
				pb->Size = Drawing::Size(32, 32);
				pb->Location = Point(r->PosicionX, r->PosicionY);
				pb->Image = r->ObtenerSpriteActual();
				pb->SizeMode = PictureBoxSizeMode::StretchImage;
				pb->BackColor = Color::Transparent;
				pb->Tag = r;
				this->Controls->Add(pb);
			}
			// Mostrar los enemgiso del nuevo mundo
			for each (Enemigo ^ enemigo in juego->ObtenerMundoActual()->Enemigos) {
				PictureBox^ pb = gcnew PictureBox();
				pb->Size = Drawing::Size(32, 32);
				pb->Location = Point(enemigo->PosicionX, enemigo->PosicionY);
				pb->Image = enemigo->ObtenerSpriteActual();
				pb->SizeMode = PictureBoxSizeMode::StretchImage;
				pb->BackColor = Color::Transparent;
				pb->Tag = enemigo;
				this->Controls->Add(pb);
			}
			for each (Aliado ^ a in juego->ObtenerMundoActual()->Aliados) {
				PictureBox^ pb = gcnew PictureBox();
				pb->Size = Drawing::Size(48, 48);
				pb->Location = Point(a->PosicionX, a->PosicionY);
				pb->Image = a->ObtenerSpriteActual();
				pb->SizeMode = PictureBoxSizeMode::StretchImage;
				pb->BackColor = Color::Transparent;
				pb->Tag = a;
				this->Controls->Add(pb);
			}
		}
	};
}
