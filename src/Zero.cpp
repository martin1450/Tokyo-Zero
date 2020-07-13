#include <SFML/Graphics.hpp>
#include <iostream>

#include "Zero.h"
#include "Personaje.h"
#include "CargaSprites.h"

using namespace sf;

Zero::Zero() : Personaje() {

    contq = 0;
    conth = 0;
    quem = false;
    hack = false;
    vida = 160;
    vidaini = vida; //barra vida enemigoffff
    armadura = 35;
    dano = 22;
    critico = 15;
    textura = CargaSprites::getTexture("resources/zero.png");
    textura2 = CargaSprites::getTexture("resources/zero.png");
    textura3 = CargaSprites::getTexture("resources/zero.png");
    sprite = Sprite(textura);
    spriteAtaque1 = Sprite(textura2);
    spriteImpacto1 = Sprite(textura3);
    sprite = Sprite(textura);

    sprite.setOrigin(100, 100);
    sprite.scale(0.6, 0.6);
    spriteAtaque1.scale(0.72,0.72);
    spriteImpacto1.scale(0.6,0.6);

    spriteAtaque1.setPosition(1200, 200);
    spriteImpacto1.setPosition(1200, 250);
}

int Zero::actuar() {

    int hit = dano - 20/10;

    return hit;
}

Zero::~Zero()
{
    //dtor
}
