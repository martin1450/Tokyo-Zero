#include "Colorea.h"

Colorea::Colorea()
{

}

Colorea::Colorea(sf::Uint8 red, sf::Uint8 green, sf::Uint8 blue)
{

    coloreando = sf::Color(red, green, blue);

}

Colorea::~Colorea()
{
    //dtor
}

sf::Color Colorea::getColor()
{
    return coloreando;

}

void Colorea::setColor(sf::Uint8 red, sf::Uint8 green, sf::Uint8 blue)
{

    coloreando = sf::Color(red, green, blue);

}
