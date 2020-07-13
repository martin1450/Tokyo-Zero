#include "TextoP.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Window.h"

TextoP::TextoP(int tipo)
{
    if(tipo == 1){
        //Tipo 1 para el plataformas
        if (!fuenteTexto.loadFromFile("resources/Fonts/Vintages.ttf"))
        {
            std::cerr << "Error cargando la fuente Vintages.ttf";
            exit(0);
        }
        texto.setFont(fuenteTexto);
        texto.setCharacterSize(40);
    }else if(tipo == 2){
        //Tipo 2 para el menu de pausa
        if (!fuenteTexto.loadFromFile("resources/quantummalicedrop.ttf"))
        {
            std::cerr << "Error cargando la fuente Vintages.ttf";
            exit(0);
        }
        texto.setFont(fuenteTexto);
        texto.setCharacterSize(60);
    }
}

void TextoP::Asignar(sf::Vector2f posicion, sf::String cadena){
    texto.setString(cadena);
    texto.setOrigin(texto.getGlobalBounds().width/2, 0);
    texto.setPosition(posicion);
}

TextoP::~TextoP()
{
    //dtor
}
