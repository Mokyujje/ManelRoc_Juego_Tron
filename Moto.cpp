#include "Moto.h"

Moto::Moto(float inicioX, float inicioY, ALLEGRO_COLOR colorMoto, int dirInicialX, int dirInicialY) {
    x = inicioX;
    y = inicioY;
    color = colorMoto;
    dirX = dirInicialX;
    dirY = dirInicialY;
    viva = true;
}

void Moto::mover() {
    if (viva) {
        x += dirX * VELOCIDAD;
        y += dirY * VELOCIDAD;
    }
}

void Moto::dibujar() {
    if (viva) {
        al_draw_filled_rectangle(x, y, x + TAMANO_MOTO, y + TAMANO_MOTO, color);
    }
}

void Moto::cambiarDireccion(int nuevaDirX, int nuevaDirY) {
    // Evitar giro de 180 grados
    if (dirX != 0 && nuevaDirX != 0) return;
    if (dirY != 0 && nuevaDirY != 0) return;

    dirX = nuevaDirX;
    dirY = nuevaDirY;
}

void Moto::matar() {
    viva = false;
}

float Moto::getX() { return x; }
float Moto::getY() { return y; }
int Moto::getDirX() { return dirX; }
int Moto::getDirY() { return dirY; }
bool Moto::estaViva() { return viva; }