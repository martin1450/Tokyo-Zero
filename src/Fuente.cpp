#include "Fuente.h"
#include "Ventana.h"
#include <SFML/Graphics.hpp>
#include <iostream>

Fuente::Fuente()
{
    if (!fuenteTexture.loadFromFile("resources/FuenteDesactivada.png"))
    {
        std::cerr << "Error cargando la imagen fuente.png";
        exit(0);
    }
}

void Fuente::Cargar(sf::Vector2f position){
    fontSprite.setTexture(fuenteTexture);
    fontSprite.setOrigin(fuenteTexture.getSize().x/2,fuenteTexture.getSize().y/2);
    fontSprite.setScale(0.4f,0.4f);
    fontSprite.setPosition(position);
    usada = false;
}

void Fuente::Activar(){
    usada = true;
    if (!fuenteTexture.loadFromFile("resources/FuenteActivada.png"))
    {
        std::cerr << "Error cargando la imagen fuente.png";
        exit(0);
    }
    Ventana::getInstancia()->sonido->PlaySound(7);
}

Fuente::~Fuente()
{
    //dtor
}
