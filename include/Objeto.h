#ifndef OBJETO_H
#define OBJETO_H
#include <SFML/Graphics.hpp>


class Objeto
{
    public:
        Objeto();

        void Cargar(sf::Vector2f position, int tipo);
        void Levitar();

        sf::Sprite& getObjectSprite(){ return objectSprite;};
        sf::Vector2f GetPosition() {return objectSprite.getPosition();};
        bool& GetCogido() {return cogido;}
        void setCogido(bool x){cogido = x;};

        int& getTipo(){return tipo;};

        virtual ~Objeto();
    protected:
    private:
        int tipo;
        bool cogido;

        sf::Vector2f posicionOriginal;
        bool levitacionSuperior;

        sf::Sprite objectSprite;
        sf::Texture objectTexture;
};

#endif // OBJETO_H
