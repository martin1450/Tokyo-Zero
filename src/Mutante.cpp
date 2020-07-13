#include <SFML/Graphics.hpp>
#include <iostream>

#include "Mutante.h"
#include "Personaje.h"
#include "CargaSprites.h"

Mutante::Mutante() {

    contq = 0;
    conth = 0;
    quem = false;
    hack = false;
    vida = 60;
    vidaini = vida; //barra vida enemigoffff
    armadura = 10;
    dano = 25;
    critico = 15;
    textura = CargaSprites::getTexture("resources/mutante.png");
    textura2 = CargaSprites::getTexture("resources/mutante.png");
    textura3 = CargaSprites::getTexture("resources/mutante.png");
    sprite = Sprite(textura);
    spriteAtaque1 = Sprite(textura2);
    spriteImpacto1 = Sprite(textura3);
    sprite = Sprite(textura);

    sprite.scale(0.5, 0.5);
    spriteAtaque1.scale(0.72,0.72);
    spriteImpacto1.scale(0.6,0.6);

    spriteAtaque1.setPosition(1200, 170);
    spriteImpacto1.setPosition(1200, 220);
}

int Mutante::actuar() {

    int hit = dano - 20/10;

    return hit;
}

Mutante::~Mutante()
{
    //dtor
}
