#ifndef NPC_H
#define NPC_H
#include <SFML/Graphics.hpp>



class Npc
{
    public:
        Npc();
        void cargar(sf::Vector2f posicion, int tipo);
        void movimiento();
        sf::Sprite& getEnemigos(){ return enemigos;};

        bool& getCambio(){return cambio;};
        void setCambio(bool x){cambio=x;};
        bool& getLuchado(){return luchado;};
        void setLuchado(bool x){luchado=x;};

        sf::Vector2f& getPosicionInicial(){return posini;};
        void setPosicionInicial(sf::Vector2f posicion);

        int& getTipo(){return tipo;};
        virtual ~Npc();

    protected:
    private:
    sf::Vector2f posini;
    int tipo;
    bool luchado = false;
    bool cambio=false;
    sf::Sprite enemigos;
    sf::Texture enemigosTexture;
    float speed = 250.0f;
    bool flip = false;
    float totalTime = 0.0f;
    float switchTime = 0.2;
    sf::IntRect uvRect;
    sf::Vector2u currentImage1;
    sf::Vector2u imageCount1;
    int entra;

};

#endif // NPC_H
