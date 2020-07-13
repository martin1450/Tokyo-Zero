#include "Puerta.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <iostream>
Puerta::Puerta()
{
    //ctor
}

void Puerta::Cargar(sf::Vector2f position, bool deFinal, sf::String pngImage, bool conKey){
    deFinal = deFinal;
    bloqueada = true;
    conKey = conKey;
    if (!puertaTexture.loadFromFile(pngImage))
    {
        std::cerr << "Error cargando la imagen de la puerta";
        exit(0);
    }

    puertaSprite.setTexture(puertaTexture);
    puertaSprite.setOrigin(puertaTexture.getSize().x/2,puertaTexture.getSize().y/2);
    puertaSprite.setScale(0.4f,0.4f);
    puertaSprite.setPosition(position);
}

void Puerta::Desbloquear(){
    if (!puertaTexture.loadFromFile("resources/puertaAbierta.png"))
    {
        std::cerr << "Error cargando la imagen de la puerta";
        exit(0);
    }
}

Puerta::~Puerta()
{
    //dtor
}
