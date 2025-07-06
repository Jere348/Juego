#pragma once
#include "Juego.h"          // lógica del juego (clase ::Juego)
#include "Configuracion.h"   // parámetros desde archivo

/*  Este archivo reemplaza por completo al antiguo formulario "MyForm".
    Está dentro del namespace GUI ==> Juego   (el mismo que usa el menú)
    La clase lógica central se llama también Juego, por eso la referenciamos
    con el operador de ámbito ::Juego para evitar ambigüedades.
*/

namespace Juego
{
    using namespace System;
    using namespace System::ComponentModel;
    using namespace System::Collections;
    using namespace System::Windows::Forms;
    using namespace System::Data;
    using namespace System::Drawing;

    public ref class MyFormJuego : public System::Windows::Forms::Form
    {
    public:
        MyFormJuego()
        {
            InitializeComponent();

            // doble buffer para un render fluido
            this->SetStyle(ControlStyles::AllPaintingInWmPaint |
                ControlStyles::UserPaint |
                ControlStyles::OptimizedDoubleBuffer, true);
            this->UpdateStyles();

            InicializarJuego();
        }

    protected:
        ~MyFormJuego()
        {
            if (components) delete components;
        }

        /* ----------  CAMPOS  ---------- */
    private:
        System::ComponentModel::Container^ components;
        Logica::Juego^ juego;
        // lógica principal
        PictureBox^ pbJugador;
        Timer^ timerJuego;
        bool teclaIzquierda = false;
        bool teclaDerecha = false;
        bool teclaArriba = false;
        bool teclaAbajo = false;
        int  framesInvulnerable = 0;   // reservado si lo necesitas

        /* ----------  DISEÑO  ---------- */
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

            this->Load += gcnew System::EventHandler(this, &MyFormJuego::MyForm_Load);
            this->KeyUp += gcnew KeyEventHandler(this, &MyFormJuego::Form_KeyUp);
            this->KeyDown += gcnew KeyEventHandler(this, &MyFormJuego::Form_KeyDown);
        }
#pragma endregion

        /* ----------  MÉTODOS PRINCIPALES  ---------- */
    private:
        // crea el juego, fondo y temporizador
        void InicializarJuego()
        {
            int anchoMapa = this->ClientSize.Width;
            int altoMapa = this->ClientSize.Height;

            Configuracion::CargarParametrosDesdeArchivo("Parameters.txt");
            juego = gcnew Logica::Juego(anchoMapa, altoMapa);

            // ----- jugador -------------------------------------------------
            this->SetStyle(ControlStyles::SupportsTransparentBackColor, true);
            this->BackColor = Color::Transparent;

            pbJugador = gcnew PictureBox();
            pbJugador->Size = Drawing::Size(48, 48);
            pbJugador->Location = Point(juego->Jugador->PosicionX, juego->Jugador->PosicionY);
            pbJugador->Image = juego->Jugador->ObtenerSpriteActual();
            pbJugador->SizeMode = PictureBoxSizeMode::StretchImage;
            pbJugador->BackColor = Color::Transparent;
            this->Controls->Add(pbJugador);
            pbJugador->BringToFront();

            // ----- fondo inicial -------------------------------------------
            this->BackgroundImage = juego->ObtenerMundoActual()->Background;
            this->BackgroundImageLayout = ImageLayout::Stretch;

            // ----- temporizador principal ----------------------------------
            timerJuego = gcnew Timer();
            timerJuego->Interval = 100;       // 10 FPS
            timerJuego->Tick += gcnew EventHandler(this, &MyFormJuego::ActualizarJuego);
            timerJuego->Start();
        }

        // bucle principal ---------------------------------------------------
        void ActualizarJuego(Object^ sender, EventArgs^ e)
        {
            int ancho = this->ClientSize.Width;
            int alto = this->ClientSize.Height;

            // movimiento
            if (teclaIzquierda) juego->Jugador->Mover("izquierda", ancho, alto);
            if (teclaDerecha)  juego->Jugador->Mover("derecha", ancho, alto);
            if (teclaArriba)   juego->Jugador->Mover("arriba", ancho, alto);
            if (teclaAbajo)    juego->Jugador->Mover("abajo", ancho, alto);

            // sprite jugador
            pbJugador->Location = Point(juego->Jugador->PosicionX, juego->Jugador->PosicionY);
            pbJugador->Image = juego->Jugador->ObtenerSpriteActual();

            // enemigos ----------------------------------------------
            juego->MoverEnemigosDelMundoActual(ancho);

            for each (Control ^ c in this->Controls) {
                PictureBox^ pb = dynamic_cast<PictureBox^>(c);
                if (pb) {
                    Enemigo^ enemigo = dynamic_cast<Enemigo^>(pb->Tag);
                    if (enemigo) {
                        pb->Location = Point(enemigo->PosicionX, enemigo->PosicionY);
                        pb->Image = enemigo->ObtenerSpriteActual();
                    }
                }
            }

            // HUD ---------------------------------------------------
            this->Text = "Vidas: " + juego->Jugador->Vidas.ToString() +
                " | Tiempo: " + juego->TiempoRestante.ToString();

            // estados fin / victoria --------------------------------
            if (juego->JuegoTerminado) {
                timerJuego->Stop();
                MessageBox::Show("¡PERDISTE!", "Fin del juego");
            }
            if (juego->VerificarVictoria()) {
                timerJuego->Stop();
                MessageBox::Show("¡GANASTE!", "Victoria");
            }

            // colisiones con enemigos --------------------------------
            for each (Control ^ c in this->Controls) {
                PictureBox^ pb = dynamic_cast<PictureBox^>(c);
                if (pb) {
                    Enemigo^ enemigo = dynamic_cast<Enemigo^>(pb->Tag);
                    if (enemigo && pb->Bounds.IntersectsWith(pbJugador->Bounds)) {
                        juego->Jugador->PerderVida();

                        // teletransporta al mundo "vacío" (índice 2)
                        CambiarMundo(2);

                        MessageBox::Show("¡Has sido atacado! Vida -1", "¡Cuidado!", MessageBoxButtons::OK, MessageBoxIcon::Warning);

                        juego->Jugador->PosicionX = 100;
                        juego->Jugador->PosicionY = 100;
                        pbJugador->Location = Point(100, 100);
                        break; // evita múltiples colisiones en el mismo frame
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

            juego->ActualizarEstado(ancho);
        }

        /* ----------  EVENTOS DE TECLADO  ---------- */
        void Form_KeyDown(Object^ sender, KeyEventArgs^ e)
        {
            // banderas de movimiento
            if (e->KeyCode == Keys::Left)  teclaIzquierda = true;
            if (e->KeyCode == Keys::Right) teclaDerecha = true;
            if (e->KeyCode == Keys::Up)    teclaArriba = true;
            if (e->KeyCode == Keys::Down)  teclaAbajo = true;

            // cambio de mundo ---------------------------------------
            if (e->KeyCode == Keys::D1)      CambiarMundo(0);
            else if (e->KeyCode == Keys::D2) CambiarMundo(1);
            else if (e->KeyCode == Keys::D3) CambiarMundo(2);

            // interacción E -----------------------------------------
            if (e->KeyCode == Keys::E) {
                // recolectar recursos -----------------------------
                for each (Control ^ c in this->Controls) {
                    PictureBox^ pb = dynamic_cast<PictureBox^>(c);
                    if (pb && pb != pbJugador) {
                        Recurso^ recurso = dynamic_cast<Recurso^>(pb->Tag);
                        if (recurso && pbJugador->Bounds.IntersectsWith(pb->Bounds)) {
                            juego->Jugador->Recolectar(recurso);
                            this->Controls->Remove(pb);
                            juego->ObtenerMundoActual()->Recursos->Remove(recurso);
                            break;
                        }
                    }
                }
                // ayudar aliados ---------------------------------
                for each (Control ^ c in this->Controls) {
                    PictureBox^ pb = dynamic_cast<PictureBox^>(c);
                    if (pb) {
                        Aliado^ aliado = dynamic_cast<Aliado^>(pb->Tag);
                        if (aliado && pb->Bounds.IntersectsWith(pbJugador->Bounds)) {
                            aliado->Ayudar(juego->Jugador);
                            MessageBox::Show("Aliado te ha ayudado. +1 Vida", "Gracias", MessageBoxButtons::OK, MessageBoxIcon::Information);
                        }
                    }
                }
                // colocar recurso en Mundo 3 ----------------------
                if (juego->ObtenerMundoActual() == juego->Mundos[2]) {
                    Recurso^ recursoColocado = juego->Jugador->ColocarRecurso();
                    if (recursoColocado) {
                        recursoColocado->PosicionX = juego->Jugador->PosicionX;
                        recursoColocado->PosicionY = juego->Jugador->PosicionY;
                        juego->ObtenerMundoActual()->Recursos->Add(recursoColocado);

                        PictureBox^ pb = gcnew PictureBox();
                        pb->Size = Drawing::Size(32, 32);
                        pb->Location = Point(recursoColocado->PosicionX, recursoColocado->PosicionY);
                        pb->Image = recursoColocado->ObtenerSpriteActual();
                        pb->SizeMode = PictureBoxSizeMode::StretchImage;
                        pb->BackColor = Color::Transparent;
                        pb->Tag = recursoColocado;
                        this->Controls->Add(pb);

                        pb->BringToFront();
                        pbJugador->BringToFront();
                    }
                }
            }
        }

        void Form_KeyUp(Object^ sender, KeyEventArgs^ e)
        {
            if (e->KeyCode == Keys::Left)  teclaIzquierda = false;
            if (e->KeyCode == Keys::Right) teclaDerecha = false;
            if (e->KeyCode == Keys::Up)    teclaArriba = false;
            if (e->KeyCode == Keys::Down)  teclaAbajo = false;
        }

        /* ----------  OTROS  ---------- */
        void MyForm_Load(System::Object^ sender, System::EventArgs^ e) {}

        // cambia entre mundos y redibuja los elementos ------------
        void CambiarMundo(int nuevoIndice)
        {
            juego->CambiarMundo(nuevoIndice);
            this->BackgroundImage = juego->ObtenerMundoActual()->Background;

            // limpiar controles existentes (excepto jugador) ------
            List<Control^>^ paraEliminar = gcnew List<Control^>();
            for each (Control ^ c in this->Controls) {
                PictureBox^ pb = dynamic_cast<PictureBox^>(c);
                if (pb && pb != pbJugador) paraEliminar->Add(pb);
            }
            for each (Control ^ pb in paraEliminar) this->Controls->Remove(pb);

            // dibujar recursos ------------------------------------
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
            // dibujar enemigos -----------------------------------
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
            // dibujar aliados ------------------------------------
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

            pbJugador->BringToFront();
        }
    };
}