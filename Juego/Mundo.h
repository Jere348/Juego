#pragma once
#include "Entidad.h"
#include "Recurso.h"
#include "Enemigo.h"
#include "Aliado.h"
#include "PersonajePrincipal.h"
using namespace System;
using namespace System::Collections::Generic;
using namespace System::Drawing;

public ref class Mundo {
public:
    String^ Nombre;
    Image^ Background;
    List<Recurso^>^ Recursos;
    List<Enemigo^>^ Enemigos;
    List<Aliado^>^ Aliados;

    Mundo(String^ nombre, String^ rutaFondo) {
        Nombre = nombre;
        Background = Image::FromFile(rutaFondo);
        Recursos = gcnew List<Recurso^>();
        Enemigos = gcnew List<Enemigo^>();
        Aliados = gcnew List<Aliado^>();
    }

    void AgregarRecurso(Recurso^ r) {
        Recursos->Add(r);
    }

    void AgregarEnemigo(Enemigo^ e) {
        Enemigos->Add(e);
    }

    void AgregarAliado(Aliado^ a) {
        Aliados->Add(a);
    }

    void ActualizarEntidades() {
        for each (Enemigo ^ e in Enemigos) {
            e->Mover("izquierda"); // ejemplo simple
        }
        for each (Aliado ^ a in Aliados) {
            a->Mover("derecha"); // ejemplo simple
        }
    }
    void GenerarRecursos(String^ nombreBase, TipoRecurso tipo, int cantidad) {
        Random^ rnd = gcnew Random();
        for (int i = 0; i < cantidad; i++) {
            Recurso^ r = gcnew Recurso(nombreBase, tipo, 10);
            r->PosicionX = rnd->Next(100, 700);
            r->PosicionY = rnd->Next(100, 500);
            Recursos->Add(r);
        }
    }
};
