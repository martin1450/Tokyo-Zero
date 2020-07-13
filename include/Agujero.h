#ifndef AGUJERO_H
#define AGUJERO_H
#include <SFML/Graphics.hpp>

class Agujero
{
    public:
        Agujero();
        void Rotar();
        void Cargar(sf::Vector2f positionAgujero1, sf::Vector2f positionAgujero2);

        sf::Sprite& getAgujero1Sprite(){ return agujero1Sprite;};
        sf::Sprite& getAgujero2Sprite(){ return agujero2Sprite;};
        virtual ~Agujero();
    protected:
    private:
        sf::Sprite agujero1Sprite;
        sf::Sprite agujero2Sprite;
        sf::Texture agujeroTexture;
};

#endif // AGUJERO_H
