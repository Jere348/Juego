#pragma once
#include "Entidad.h"
#include "PersonajePrincipal.h"

public ref class Enemigo : public Entidad {
public:
    int NivelDificultad;
    int Danio;

    Enemigo(int dificultad) {
        NivelDificultad = dificultad;
        Danio = dificultad * 10;
        CargarSpritesEnemigo();
    }

    void Atacar(PersonajePrincipal^ p) {
        p->Energia -= Danio;
    }

private:
    void CargarSpritesEnemigo() {
        SpritesMovimiento->Add(Image::FromFile("sprites/enemigo1.png"));
        SpritesMovimiento->Add(Image::FromFile("sprites/enemigo2.png"));
    }
};
