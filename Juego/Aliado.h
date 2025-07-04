#pragma once
#include "Entidad.h"
#include "PersonajePrincipal.h"

public ref class Aliado : public Entidad {
public:
    String^ MundoPertenece;
    String^ TipoAyuda;

    Aliado(String^ mundo) {
        MundoPertenece = mundo;
        CargarSpritesAliado();
    }

    void Ayudar(PersonajePrincipal^ p) {
        p->Energia += 10;
    }

private:
    void CargarSpritesAliado() {
        SpritesMovimiento->Add(Image::FromFile("aliado1.png"));
        SpritesMovimiento->Add(Image::FromFile("aliado2.png"));
        SpritesMovimiento->Add(Image::FromFile("aliado3.png"));
        SpritesMovimiento->Add(Image::FromFile("aliado4.png"));
    }
};
