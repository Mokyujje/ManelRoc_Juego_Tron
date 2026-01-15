#pragma once
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

#define TAMANO_MOTO 10
#define VELOCIDAD 10

class Moto {
private:
    float x, y;
    int dirX, dirY;
    ALLEGRO_COLOR color;
    bool viva;

public:
    Moto(float inicioX, float inicioY, ALLEGRO_COLOR colorMoto, int dirInicialX, int dirInicialY);

    void mover();
    void dibujar();
    void cambiarDireccion(int nuevaDirX, int nuevaDirY);
    void matar();
    float getX();
    float getY();
    int getDirX();
    int getDirY();
    bool estaViva();
};