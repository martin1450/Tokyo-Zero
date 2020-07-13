#ifndef ANIMASPRITES_H
#define ANIMASPRITES_H

#include <SFML/Graphics.hpp>

class AnimaSprites
{
    public:
        AnimaSprites(std::string nombre, int spritesX, int spritesY, int inicioSprite, int numeroSprites, float tiempoPorFrame);
        void animar();
        sf::Sprite& getSprite();
        virtual ~AnimaSprites();
    protected:
    private:
        int frameX;
        int frameY;
        int finalX;
        int iniX;
        int iniY;
        int numero;
        int actual;
        float tiempo;
        sf::IntRect recorte;
        sf::Texture textura;
        sf::Sprite sprite;
        sf::Clock relojSprite;
};

#endif // ANIMASPRITES_H
