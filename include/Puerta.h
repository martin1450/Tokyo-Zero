#ifndef PUERTA_H
#define PUERTA_H
#include <SFML/Graphics.hpp>


class Puerta
{
    public:
        Puerta();
        void Cargar(sf::Vector2f position, bool deFinal, sf::String pngImage, bool conKey);

        void Desbloquear();

        sf::Sprite& getPuertaSprite(){ return puertaSprite;};

        bool& getBloqueada() {return bloqueada;};
        void setBloqueada(bool x){bloqueada = x;};

        bool& getDeFinal(){return deFinal;};
        bool& getConKey(){return conKey;};

        virtual ~Puerta();
    protected:
    private:
        bool bloqueada;
        bool deFinal;
        bool conKey;
        sf::Sprite puertaSprite;
        sf::Texture puertaTexture;
};

#endif // PUERTA_H
