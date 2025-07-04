#pragma once
#include "Entidad.h"

public enum class TipoRecurso { Humano, Tecnologico };

public ref class Recurso : public Entidad {
public:
	String^ Nombre;
	TipoRecurso Tipo;
	int Valor;
	int ID;

	static int contadorID = 0;

	Recurso(String^ nombre, TipoRecurso tipo, int valor) {
		ID = contadorID++;
		Nombre = nombre;
		Tipo = tipo;
		Valor = valor;
		// sprite aleatorio
		// Cargar sprite específico por nombre
		SpritesMovimiento = gcnew List<Image^>();
		if (nombre == "Arbol")
			SpritesMovimiento->Add(Image::FromFile("RecursoN1.png"));
		else if (nombre == "Arbusto")
			SpritesMovimiento->Add(Image::FromFile("RecursoN2.png"));
		else if (nombre == "Molino")
			SpritesMovimiento->Add(Image::FromFile("RecursoN3.png"));
		else if (nombre == "Fabrica")
			SpritesMovimiento->Add(Image::FromFile("RecursoT1.png"));
		else if (nombre == "Nuclear")
			SpritesMovimiento->Add(Image::FromFile("RecursoT2.png"));
		else if (nombre == "Edificios")
			SpritesMovimiento->Add(Image::FromFile("RecursoT3.png"));
	}
};
