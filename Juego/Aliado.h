#pragma once
#include "Entidad.h"
#include "PersonajePrincipal.h"

public ref class Aliado : public Entidad {
public:
	String^ MundoPertenece;
	String^ TipoAyuda;

	// Constructor original (sin posición)
	Aliado(String^ mundo) {
		MundoPertenece = mundo;
		CargarSpritesAliado();
	}

	//  Constructor con posición directa
	Aliado(String^ mundo, int x, int y) {
		MundoPertenece = mundo;
		PosicionX = x;
		PosicionY = y;
		CargarSpritesAliado();
	}

	void Ayudar(PersonajePrincipal^ p) {
		p->Vidas += 1;
	}

private:
	void CargarSpritesAliado() {
		SpritesMovimiento = gcnew List<Image^>();
		if (MundoPertenece == "Mundo Humano") {
			Image^ sheetIzq = Image::FromFile("viejo sabio aliado.png");
			SpritesMovimiento = CortarSpriteSheet(sheetIzq, 3);
			TipoAyuda = "Humano";
		}
		else if (MundoPertenece == "Mundo Tecnológico") {
			Image^ sheetIzq = Image::FromFile("robot aliado1.png");
			SpritesMovimiento = CortarSpriteSheet(sheetIzq, 10);
			TipoAyuda = "Tecnológico";
		}
		else {

		}
	}
};

