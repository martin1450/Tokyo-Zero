#include "Objeto.h"
#include <SFML/Graphics.hpp>
#include "Ventana.h"
#include <iostream>

Objeto::Objeto(){}


void Objeto::Cargar(sf::Vector2f position, int tipoObjeto){

    switch(tipoObjeto){
        case 1:
            {
                if (!objectTexture.loadFromFile("resources/pocion.png"))
                {
                    std::cerr << "Error cargando la imagen armadura.png";
                    exit(0);
                }
                break;
            }
        case 2:
            {
                if (!objectTexture.loadFromFile("resources/armadura.png"))
                {
                    std::cerr << "Error cargando la imagen armadura.png";
                    exit(0);
                }
                break;
            }
        case 3:
            {
                if (!objectTexture.loadFromFile("resources/keycard.png"))
                {
                    std::cerr << "Error cargando la imagen armadura.png";
                    exit(0);
                }
                break;
            }
        case 4:
            {
                if (!objectTexture.loadFromFile("resources/coin.png"))
                {
                    std::cerr << "Error cargando la imagen armadura.png";
                    exit(0);
                }
                break;
            }
    }

    objectSprite.setTexture(objectTexture);
    objectSprite.setOrigin(objectTexture.getSize().x/2,objectTexture.getSize().y/2);
    objectSprite.setScale(0.2f,0.2f);
    objectSprite.setPosition(position);
    cogido = false;
    tipo = tipoObjeto;
    posicionOriginal = position;
}

void Objeto::Levitar(){
    if(!levitacionSuperior && objectSprite.getPosition().y > posicionOriginal.y - 5.0f){
        objectSprite.move(0, -3*Ventana::getInstancia()->delta);
        if(objectSprite.getPosition().y < posicionOriginal.y - 5.0f)
            levitacionSuperior = true;
    }else if(levitacionSuperior && objectSprite.getPosition().y < posicionOriginal.y + 4.0f){
        objectSprite.move(0, 3*Ventana::getInstancia()->delta);
        if(objectSprite.getPosition().y > posicionOriginal.y + 4.0f)
            levitacionSuperior = false;
    }

}


Objeto::~Objeto()
{
    //dtor
}
