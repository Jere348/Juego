#pragma once
#include "Entidad.h"
#include "Recurso.h"

public ref class PersonajePrincipal : public Entidad {
public:
    int Vidas;
    int Energia;
    List<Recurso^>^ Inventario;

    PersonajePrincipal() {
        Vidas = 3;
        Energia = 100;
        Inventario = gcnew List<Recurso^>();
        CargarSpritesJugador();
    }

    void Recolectar(Recurso^ recurso) {
        Inventario->Add(recurso);
    }

    void PerderVida() {
        Vidas--;
    }
    void ColocarRecurso(List<Recurso^>^ mundo3, int x, int y) {
        if (Inventario->Count > 0) {
            Recurso^ r = Inventario[0];
            r->PosicionX = x;
            r->PosicionY = y;
            mundo3->Add(r);
            Inventario->RemoveAt(0);
        }
    }
private:
    void CargarSpritesJugador() {
        SpritesMovimiento->Add(Image::FromFile("trainer.front1.png"));
        SpritesMovimiento->Add(Image::FromFile("trainer.front2.png"));
        SpritesMovimiento->Add(Image::FromFile("trainer.front3.png"));
    }
};
