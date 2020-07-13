#ifndef COLOREA_H
#define COLOREA_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

class Colorea
{
    public:
        Colorea();
        Colorea(sf::Uint8 red, sf::Uint8 green, sf::Uint8 blue);
        virtual ~Colorea();
        sf::Color getColor();
        void setColor(sf::Uint8 red, sf::Uint8 green, sf::Uint8 blue);
    protected:
    private:
        sf::Color coloreando;
};

#endif // COLOREA_H
