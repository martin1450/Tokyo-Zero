#ifndef MENU_H
#define MENU_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Colorea.h"
#include "Texto.h"
#include "Eplat.h"
#define numMaxItems 4


class Menu
{

    public:
        Menu();
        virtual ~Menu();

        void mUp();
        void mDown();
        int botonPresionado();
        void procesEvent();
        void dibujar();
        void muestraV();

        std::array<Texto, numMaxItems>* getTextos();

    private:
        int seleccionado;
        int x;
        int y;
        sf::Event eventoGame;
        sf::Texture textura;
        sf::Sprite spriteFondo;
        sf::Sprite sprite2;
        bool aux;

        bool dibujarControles = false;
        //sf::Text texto[numMaxItems];

        std::array<Texto, numMaxItems> texto;

        Eplat eplat;
        sf::Sprite controles;
        sf::Texture controlesTexture;

        sf::RectangleShape transparencia;

};

#endif // MENU_H
