#include <SFML/Graphics.hpp>
#include <iostream>

#include "Soldado.h"
#include "Personaje.h"
#include "CargaSprites.h"

using namespace sf;

Soldado::Soldado() : Personaje() {

    contq = 0;
    conth = 0;
    quem = false;
    hack = false;
    vida = 80;
    vidaini = vida; //barra vida enemigoffff
    armadura = 15;
    dano = 20;
    critico = 15;
    textura = CargaSprites::getTexture("resources/oni.png");
    textura2 = CargaSprites::getTexture("resources/oni.png");
    textura3 = CargaSprites::getTexture("resources/oni.png");
    sprite = Sprite(textura);
    spriteAtaque1 = Sprite(textura2);
    spriteImpacto1 = Sprite(textura3);
    sprite = Sprite(textura);

    sprite.scale(0.5, 0.5);
    spriteAtaque1.scale(0.72,0.72);
    spriteImpacto1.scale(0.6,0.6);

    spriteAtaque1.setPosition(1200, 150);
    spriteImpacto1.setPosition(1200, 210);
}

int Soldado::actuar() {

    int hit = dano - 20/10;

    return hit;
}

Soldado::~Soldado()
{
    //dtor
}
