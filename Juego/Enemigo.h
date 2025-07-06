public ref class Enemigo : public Entidad {
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
		if (MoverDerecha) {
			PosicionX += VelocidadX;
			SpritesMovimiento = SpritesDerecha;
		}
		else {
			PosicionX -= VelocidadX;
			SpritesMovimiento = SpritesIzquierda;
		}

		// Rebotar en bordes
		if (PosicionX <= 0) MoverDerecha = true;
		else if (PosicionX >= anchoMapa - 32) MoverDerecha = false;

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
		
	}
};