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
        SpritesMovimiento->Add(Image::FromFile("robot aliado1.png"));
    }
};
