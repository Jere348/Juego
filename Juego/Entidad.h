#pragma once

using namespace System;
using namespace System::Collections::Generic;
using namespace System::Drawing;

public ref class Entidad abstract {
public:
    int PosicionX;
    int PosicionY;
    List<Image^>^ SpritesMovimiento;
    int FrameActual;

    Entidad() {
        SpritesMovimiento = gcnew List<Image^>();
        FrameActual = 0;
    }

    virtual void Mover(String^ direccion) {
        if (direccion == "izquierda") PosicionX -= 5;
        else if (direccion == "derecha") PosicionX += 5;
        else if (direccion == "arriba") PosicionY -= 5;
        else if (direccion == "abajo") PosicionY += 5;

        AvanzarAnimacion();
    }

    void AvanzarAnimacion() {
        if (SpritesMovimiento->Count > 0)
            FrameActual = (FrameActual + 1) % SpritesMovimiento->Count;
    }

    Image^ ObtenerSpriteActual() {
        return (SpritesMovimiento->Count > 0) ? SpritesMovimiento[FrameActual] : nullptr;
    }

    List<Image^>^ CortarSpriteSheet(Image^ sheet, int totalFrames) {
        List<Image^>^ frames = gcnew List<Image^>();

        int anchoFrame = sheet->Width / totalFrames;
        int altoFrame = sheet->Height;

        for (int i = 0; i < totalFrames; i++) {
            Bitmap^ frame = gcnew Bitmap(anchoFrame, altoFrame);
            Graphics^ g = Graphics::FromImage(frame);
            g->DrawImage(sheet,
                Rectangle(0, 0, anchoFrame, altoFrame),              // destino
                Rectangle(i * anchoFrame, 0, anchoFrame, altoFrame), // origen
                GraphicsUnit::Pixel);
            frames->Add(frame);
        }

        return frames;
    }

};