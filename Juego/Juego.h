#pragma once
#include "Mundo.h"
using namespace System;
using namespace System::Collections::Generic;

public ref class Juego {
public:

    List<Mundo^>^ Mundos;
    PersonajePrincipal^ Jugador;
    int IndiceMundoActual;
    int TiempoRestante;
    bool JuegoTerminado;

    Juego(int anchoMapa, int altoMapa) {
        Mundos = gcnew List<Mundo^>();
        Jugador = gcnew PersonajePrincipal();
        IndiceMundoActual = 3;
        TiempoRestante = 300;
        JuegoTerminado = false;

        InicializarMundos(anchoMapa, altoMapa);
    }

    void InicializarMundos(int anchoMapa, int altoMapa) {
        Mundo^ mundo1 = gcnew Mundo("Mundo Humano", "Mundo 1.png");
        mundo1->GenerarRecursosAleatorios(TipoRecurso::Humano, 10, anchoMapa, altoMapa);
        mundo1->AgregarAliado(gcnew Aliado("Mundo Humano"));
        mundo1->AgregarEnemigo(gcnew Enemigo(1));

        Mundo^ mundo2 = gcnew Mundo("Mundo Tecnológico", "Mundo 2.png");
        mundo2->GenerarRecursosAleatorios(TipoRecurso::Tecnologico, 10, anchoMapa, altoMapa);
        mundo2->AgregarAliado(gcnew Aliado("Mundo Tecnológico"));
        mundo2->AgregarEnemigo(gcnew Enemigo(2));

        Mundo^ mundo3 = gcnew Mundo("Mundo Blanco", "Mundo 3.png");

        Mundos->Add(mundo1);
        Mundos->Add(mundo2);
        Mundos->Add(mundo3);
    }


    Mundo^ ObtenerMundoActual() {
        return Mundos[IndiceMundoActual];
    }

    void CambiarMundo(int nuevoIndice) {
        if (nuevoIndice >= 0 && nuevoIndice < Mundos->Count) {
            IndiceMundoActual = nuevoIndice;
        }

    }

    void ActualizarEstado() {
        ObtenerMundoActual()->ActualizarEntidades();
        TiempoRestante--;

        if (TiempoRestante <= 0 || Jugador->Vidas <= 0) {
            JuegoTerminado = true;
        }
    }

    bool VerificarVictoria() {
        // Aquí se define si construiste 80% del mundo 3
        return false; // lógica futura
    }
};
