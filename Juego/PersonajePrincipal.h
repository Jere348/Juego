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
    Recurso^ ColocarRecurso() {
        if (Inventario->Count == 0) return nullptr;

        Recurso^ r = Inventario[0];
        Inventario->RemoveAt(0);
        return r;
    }
private:
    void CargarSpritesJugador() {
        SpritesMovimiento->Add(Image::FromFile("trainer.front1.png"));
        SpritesMovimiento->Add(Image::FromFile("trainer.front2.png"));
        SpritesMovimiento->Add(Image::FromFile("trainer.front3.png"));
    }
};
