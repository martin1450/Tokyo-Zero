#include <SFML/Graphics.hpp>
#include <iostream>

#include "AnimaSprites.h"
#include "CargaSprites.h"

using namespace sf;

AnimaSprites::AnimaSprites(std::string nombre, int spritesX, int spritesY, int inicioSprite, int numeroSprites, float tiempoPorFrame) {
// PASAMOS:  Fichero,  Sprites totales en X,  Sprites totales en Y, Sprite de inicio, Número de sprites a animar, Tiempo por sprite

    actual = 0;

    textura = CargaSprites::getTexture(nombre);
    tiempo = tiempoPorFrame;
    numero = numeroSprites-1;

    Vector2u tamano = textura.getSize();
    frameX = tamano.x/spritesX;
    frameY = tamano.y/spritesY;
    finalX = frameX*spritesX-frameX;
    recorte = IntRect(0, 0, frameX, frameY);

    // ENCONTRAR EL PUNTO DE INICIO
    for (int i=1; i<inicioSprite; i++) {

        if(recorte.left == finalX && i!=inicioSprite) {

            recorte.left = 0;
            recorte.top += frameY;
            i++;
        }
        else {

            if (i == inicioSprite) {

                recorte.left = frameX*inicioSprite;
                recorte.top = 0;
            }
            else {
                recorte.left += frameX;
                i++;
            }
        }
    }
    iniX = recorte.left;
    iniY = recorte.top;

    sprite = Sprite(textura, recorte);
}

void AnimaSprites::animar(){

    if(relojSprite.getElapsedTime().asSeconds() > tiempo) {

        //std::cout << "Actual: " << actual << std::endl;
        //std::cout << recorte.left << std::endl;
        //std::cout << recorte.top << std::endl;

        if(recorte.left == finalX && actual!=numero) {

            recorte.left = 0;
            recorte.top += frameY;
            actual++;
        }
        else {

            if (actual == numero) {

                recorte.left = iniX;
                recorte.top = iniY;
                actual = 0;
            }
            else {
                recorte.left += frameX;
                actual++;
            }
        }
        sprite.setTextureRect(recorte);
        relojSprite.restart();
    }
}

Sprite& AnimaSprites::getSprite() {

    return sprite;
}

AnimaSprites::~AnimaSprites()
{
    //dtor
}
