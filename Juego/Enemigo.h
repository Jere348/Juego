﻿public ref class Enemigo : public Entidad {
public:
	String^ Nombre;
	int VelocidadX;
	bool MoverDerecha;
	int NivelDificultad;
	int Danio;
	static Random^ rndGlobal = gcnew Random();
	List<Image^>^ SpritesIzquierda;
	List<Image^>^ SpritesDerecha;

	Enemigo(String^ nombre, int dificultad, int anchoMapa, int altoMapa) {
		Nombre = nombre;
		NivelDificultad = dificultad;
		Danio = dificultad * 10;
		VelocidadX = 2;
		MoverDerecha = true;

		Random^ rnd = gcnew Random();

		// Dentro del rango del mapa visible
		PosicionX = rndGlobal->Next(50, Math::Max(51, anchoMapa - 82));
		PosicionY = rndGlobal->Next(50, Math::Max(51, altoMapa - 82));
		Console::WriteLine("[" + Nombre + "] X: " + PosicionX + ", Y: " + PosicionY);



		CargarSpritesEnemigo();
	}
	void MoverAutomatico(int anchoMapa) {
		int spriteAncho = 48;

		if (MoverDerecha) {
			PosicionX += VelocidadX;

			if (PosicionX + spriteAncho >= anchoMapa) {
				PosicionX = anchoMapa - spriteAncho;
				MoverDerecha = false;
			}

			SpritesMovimiento = SpritesDerecha;
		}
		else {
			PosicionX -= VelocidadX;

			if (PosicionX <= 0) {
				PosicionX = 0;
				MoverDerecha = true;
			}

			SpritesMovimiento = SpritesIzquierda;
		}
		Console::WriteLine("[" + Nombre + "] Pos: " + PosicionX + " | Dir: " + (MoverDerecha ? "→" : "←"));

		AvanzarAnimacion();
	}


private:
	
	void CargarSpritesEnemigo() {
		SpritesIzquierda = gcnew List<Image^>();
		SpritesDerecha = gcnew List<Image^>();
		// De momento, ponemos una imagen por tipo
		if (Nombre == "Pajaro") {
			SpritesIzquierda->Add(Image::FromFile("pajaro.izquierda1.png"));
			SpritesIzquierda->Add(Image::FromFile("pajaro.izquierda2.png"));
			SpritesIzquierda->Add(Image::FromFile("pajaro.izquierda3.png"));
			SpritesIzquierda->Add(Image::FromFile("pajaro.izquierda4.png"));

			SpritesDerecha->Add(Image::FromFile("pajaro.derecha1.png"));
			SpritesDerecha->Add(Image::FromFile("pajaro.derecha2.png"));
			SpritesDerecha->Add(Image::FromFile("pajaro.derecha3.png"));
			SpritesDerecha->Add(Image::FromFile("pajaro.derecha4.png"));
		}
		else if (Nombre == "Golem") {
			Image^ sheetIzq = Image::FromFile("golem2.izquierda.png");
			SpritesIzquierda = CortarSpriteSheet(sheetIzq, 9);

			Image^ sheetDer = Image::FromFile("golem2.derecha.png");
			SpritesDerecha = CortarSpriteSheet(sheetDer, 9);

			// Valor inicial
			SpritesMovimiento = SpritesIzquierda;
		}
		else if (Nombre == "HombreRoca") {
			Image^ sheetIzq = Image::FromFile("golem.izquierda.png");
			SpritesIzquierda = CortarSpriteSheet(sheetIzq, 10);
			Image^ sheetDer = Image::FromFile("golem.derecha.png");
			SpritesDerecha = CortarSpriteSheet(sheetDer, 10);
			// Valor inicial
			SpritesMovimiento = SpritesIzquierda;
		}
		else if (Nombre == "Robot1") {
			Image^ sheetIzq = Image::FromFile("Robot1.izquierda.png");
			SpritesIzquierda = CortarSpriteSheet(sheetIzq, 3);

			Image^ sheetDer = Image::FromFile("Robot1.derecha.png");
			SpritesDerecha = CortarSpriteSheet(sheetDer, 3);

			// Valor inicial
			SpritesMovimiento = SpritesIzquierda;
		}
		else if (Nombre == "Robot2") {
			Image^ sheetIzq = Image::FromFile("Robot2.izquierda.png");
			SpritesIzquierda = CortarSpriteSheet(sheetIzq, 3);
			Image^ sheetDer = Image::FromFile("Robot2.derecha.png");
			SpritesDerecha = CortarSpriteSheet(sheetDer, 3);
			// Valor inicial
			SpritesMovimiento = SpritesIzquierda;
		}
		else if (Nombre == "Robot3") {
			Image^ sheetIzq = Image::FromFile("Robot3.izquierda.png");
			SpritesIzquierda = CortarSpriteSheet(sheetIzq, 3);
			Image^ sheetDer = Image::FromFile("Robot3.derecha.png");
			SpritesDerecha = CortarSpriteSheet(sheetDer, 3);
			// Valor inicial
			SpritesMovimiento = SpritesIzquierda;
		}
		
	}
};