#pragma once


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
		SpritesMovimiento->Add(Image::FromFile("sprites/recurso1.png"));
	}
};
