#ifndef JUGADORP_H
#define JUGADORP_H
#include <SFML/Graphics.hpp>
class JugadorP
{
    public:
        JugadorP();
        void cargar(sf::Vector2f position);
        void moverse();
        void jump();
        void comprobador();

        bool EntrarEnVortice();

        sf::Sprite& getBoy(){ return boy;};
        bool& getIsJumping(){return isJumping;};
        void setIsJumping(bool x){isJumping=x;};

        bool& getCayendo(){return cayendo;};
        bool& getSubiendo(){return subiendo;};
        void setCayendo(bool x){cayendo=x;};
        void setSubiendo(bool x){subiendo=x;};

        virtual ~JugadorP();
    protected:
    private:
        sf::Sprite boy;
        sf::Texture playerTexture;
        float speed = 500.0f; //300
        bool flip = false;
        float totalTime = 0.0f;
        float totalTime2 = 0.0f;
        float switchTime = 0.1;
        sf::IntRect uvRect;
        sf::Vector2u currentImage;
        sf::Vector2u imageCount;
        int row = 0;
        int ActualRow = 0;
        float jumpscrollspeed = 500.0f; //como speed pero en jump
        float jumpSpeed = 450.0f;
        float gravity = 650.0f; //800
        bool isJumping = false;
        bool cayendo = true;
        bool subiendo = false;
        sf::Vector2u currentImage2;
        sf::Vector2u imageCount2;
        sf::Vector2f playerVelocity;

        float contadorVortice;
        bool  entrandoEnVortice;
};

#endif // JUGADORP_H
