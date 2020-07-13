#ifndef TEXTOP_H
#define TEXTOP_H
#include <SFML/Graphics.hpp>
#include <iostream>

class TextoP
{
    public:
        TextoP(int tipo);
        sf::Text& getTexto(){return texto;};
        void Asignar(sf::Vector2f posicion, sf::String cadena);
        virtual ~TextoP();
    protected:
    private:
        sf::Font fuenteTexto;
        sf::Text texto;
};

#endif // TEXTOP_H
