#ifndef WORLD_H
#define WORLD_H
#include "State.h"

class World
{
    public:
        World();
        void inicializar(int x);
        void  bucle();
        void nuevoMundo(int plantilla);
        int getState();
        void setState(int x);
        virtual ~World();
        State state;
    protected:
    private:
        sf::Clock clockMov;

        //PAUSE MENU
        sf::Sprite pauseWindow;
        sf::Texture pauseWindowTexture;
        sf::RectangleShape pauseMask;
        TextoP * potionTextPause;
        TextoP * armorTextPause;
        sf::Sprite xiconK;
        sf::Sprite viconK;
        sf::Sprite xiconH;
        sf::Sprite viconH;
        sf::Texture xiconTexture;
        sf::Texture viconTexture;
};

#endif // WORLD_H
