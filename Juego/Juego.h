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
        IndiceMundoActual = 2;
        TiempoRestante = 300;
        JuegoTerminado = false;

        InicializarMundos(anchoMapa, altoMapa);
    }

    void InicializarMundos(int anchoMapa, int altoMapa) {
        Mundo^ mundo1 = gcnew Mundo("Mundo Humano", "Mundo 1.png");
        mundo1->GenerarRecursosAleatorios(TipoRecurso::Humano, 10, anchoMapa, altoMapa);
        mundo1->AgregarAliado(gcnew Aliado("Mundo Humano"));
        mundo1->AgregarEnemigo(gcnew Enemigo("Pajaro", 1, anchoMapa,altoMapa));
        mundo1->AgregarEnemigo(gcnew Enemigo("HombreRoca", 1, anchoMapa,altoMapa));
        mundo1->AgregarEnemigo(gcnew Enemigo("Golem", 1, anchoMapa,altoMapa));

        Mundo^ mundo2 = gcnew Mundo("Mundo Tecnológico", "Mundo 2.png");
        mundo2->GenerarRecursosAleatorios(TipoRecurso::Tecnologico, 10, anchoMapa, altoMapa);
        mundo2->AgregarAliado(gcnew Aliado("Mundo Tecnológico"));
        mundo2->AgregarEnemigo(gcnew Enemigo("Robot1", 2,anchoMapa,altoMapa));
        mundo2->AgregarEnemigo(gcnew Enemigo("Robot2", 2,anchoMapa,altoMapa));
        mundo2->AgregarEnemigo(gcnew Enemigo("Robot3", 2,anchoMapa,altoMapa));

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

    void MoverEnemigosDelMundoActual(int anchoMapa) {
        for each (Enemigo ^ enemigo in ObtenerMundoActual()->Enemigos) {
            enemigo->MoverAutomatico(anchoMapa);
        }
    }
};
