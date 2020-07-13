#include "Agujero.h"
#include "Ventana.h"
#include <iostream>

Agujero::Agujero()
{
    //ctor
}

void Agujero::Cargar(sf::Vector2f positionAgujero1, sf::Vector2f positionAgujero2){
    if (!agujeroTexture.loadFromFile("resources/vortice.png"))
    {
        std::cerr << "Error cargando la imagen agujero.png";
        exit(0);
    }

    agujero1Sprite.setTexture(agujeroTexture);
    agujero1Sprite.setOrigin(agujeroTexture.getSize().x/2,agujeroTexture.getSize().y/2);
    agujero1Sprite.setScale(0.5f,0.5f);
    agujero1Sprite.setPosition(positionAgujero1);

    agujero2Sprite.setTexture(agujeroTexture);
    agujero2Sprite.setOrigin(agujeroTexture.getSize().x/2,agujeroTexture.getSize().y/2);
    agujero2Sprite.setScale(0.5f,0.5f);
    agujero2Sprite.setPosition(positionAgujero2);
}

void Agujero::Rotar(){
    agujero1Sprite.setRotation(agujero1Sprite.getRotation() + 1.0 *Ventana::getInstancia()->delta);
    agujero2Sprite.setRotation(agujero2Sprite.getRotation() - 1.0 *Ventana::getInstancia()->delta);
}

Agujero::~Agujero()
{
    //dtor
}
