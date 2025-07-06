#pragma once

using namespace System;
using namespace System::IO;
using namespace System::Collections::Generic;
using namespace System::Windows::Forms;

public ref class Configuracion {
public:
	static int RecursosHumanos = 10;
	static int RecursosTecnologicos = 10;
	static int TiempoLimite = 300;
	static int VidasIniciales = 3;

	static void CargarParametrosDesdeArchivo(String^ ruta) {
		if (!File::Exists(ruta)) {
			MessageBox::Show("No se encontró PARAMETERS.txt en: " + ruta);
			return;
		}

		array<String^>^ lineas = File::ReadAllLines(ruta);
		for each (String ^ linea in lineas) {
			if (linea->StartsWith("#") || linea->Trim() == "") continue;

			array<String^>^ partes = linea->Split('=');
			if (partes->Length != 2) continue;

			String^ clave = partes[0]->Trim()->ToUpper();
			String^ valor = partes[1]->Trim();

			if (clave == "RECURSOS_HUMANO")
				RecursosHumanos = Int32::Parse(valor);
			else if (clave == "RECURSOS_TECNOLOGICO")
				RecursosTecnologicos = Int32::Parse(valor);
			else if (clave == "TIEMPO_LIMITE")
				TiempoLimite = Int32::Parse(valor);
			else if (clave == "VIDAS_INICIALES")
				VidasIniciales = Int32::Parse(valor);
		}
	}
};
