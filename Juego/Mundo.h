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
    int RecursosOriginalesHumanos;
    int RecursosOriginalesTecnologicos;

    Mundo(String^ nombre, String^ rutaFondo) {
        Nombre = nombre;
        Background = Image::FromFile(rutaFondo);
        Recursos = gcnew List<Recurso^>();
        Enemigos = gcnew List<Enemigo^>();
        Aliados = gcnew List<Aliado^>();
    }

    void AgregarRecurso(Recurso^ r) {
        Random^ rnd = gcnew Random();
        r->PosicionX = rnd->Next(50, 700);
        r->PosicionY = rnd->Next(50, 500);
        Recursos->Add(r);
    }

    void AgregarEnemigo(Enemigo^ e) {
        Enemigos->Add(e);
    }

    void AgregarAliado(Aliado^ a) {
        Aliados->Add(a);
    }

    void ActualizarEntidades(int anchoMapa) {
        for each (Enemigo ^ e in Enemigos) {
            e->MoverAutomatico(anchoMapa); // ← usa su movimiento automático
        }
        for each (Aliado ^ a in Aliados) {
            // Si Aliado también tiene movimiento automático, crea un método similar.
            // Por ahora lo dejamos fijo o con otro tipo de movimiento si no aplica.
        }
    }

    void GenerarRecursosAleatorios(TipoRecurso tipo, int cantidad, int anchoMapa, int altoMapa) {
        array<String^>^ nombres;

        if (tipo == TipoRecurso::Humano) {
            nombres = gcnew array<String^>{ "Arbol", "Arbusto", "Molino" };
        }
        else {
            nombres = gcnew array<String^>{ "Fabrica", "Nuclear", "Edificios" };
        }

        Random^ rnd = gcnew Random();
        List<Point>^ posicionesOcupadas = gcnew List<Point>();

        for (int i = 0; i < cantidad; i++) {
            int intentos = 0;
            Point nuevaPos;

            do {
                int x = rnd->Next(50, anchoMapa - 50);
                int y = rnd->Next(50, altoMapa - 50);
                nuevaPos = Point(x, y);
                intentos++;
            } while (YaExisteEnPosicion(posicionesOcupadas, nuevaPos) && intentos < 100);

            // Elegir tipo aleatorio
            int index = rnd->Next(0, nombres->Length);
            String^ nombreAleatorio = nombres[index];

            Recurso^ r = gcnew Recurso(nombreAleatorio, tipo, 10);
            r->PosicionX = nuevaPos.X;
            r->PosicionY = nuevaPos.Y;

            posicionesOcupadas->Add(nuevaPos);
            Recursos->Add(r);
        }
    }
    bool YaExisteEnPosicion(List<Point>^ posiciones, Point nueva) {
        for each (Point p in posiciones) {
            // Consideramos una distancia mínima entre objetos (32 px de sprite)
            if (Math::Abs(p.X - nueva.X) < 32 && Math::Abs(p.Y - nueva.Y) < 32)
                return true;
        }
        return false;
    }

};
