#ifndef FUENTE_H
#define FUENTE_H
#include <SFML/Graphics.hpp>

class Fuente
{
    public:
        Fuente();

        void Cargar(sf::Vector2f position);
        void Activar();

        sf::Sprite& getFontSprite(){ return fontSprite;};
        sf::Vector2f GetPosition() {return fontSprite.getPosition();};
        void setUsada(bool x){usada = x;};
        bool& GetUsada() {return usada;}

        virtual ~Fuente();
    protected:
    private:
        bool usada;
        sf::Sprite fontSprite;
        sf::Texture fuenteTexture;
};

#endif // FUENTE_H
