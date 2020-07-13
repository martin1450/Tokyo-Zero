#ifndef VENTANA_H
#define VENTANA_H
#include "World.h"
#include "Sonidos.h"
#include "LevelFactory.h"
#include <SFML/Graphics.hpp>

class Ventana
{
    public:
        static Ventana* getInstancia();
        float delta = 0.0f;
        float percent =0.0f;
        int tamX;
        int tamY;
        int updates;
        World world;
        Sonidos* sonido;
        sf::RenderWindow window;
        sf::Vector2f firstpos;
        sf::Vector2f lastpos;
        sf::Vector2f firstposnpc;
        sf::Vector2f lastposnpc;
        sf::Clock clockMov;
        sf::Clock clockInt;
        LevelFactory factory;
        sf::Sprite fondo;
        sf::Texture fondoTexture;
        sf::Sprite fin;
        sf::Texture finTexture;
        sf::View camera;
        sf::Vector2f cameraPosition;

        bool pausa;

        int colisones [120*33];
        int direccion = 0;
        sf::RectangleShape rectangulo;
        bool caida;
        bool agachado;

        int& getPociones(){return pociones;};
        int& getArmadura(){return armadura;};
        bool& getHabilidaExtra(){return habilidadExtra;};
        bool& getkeyCard(){return keyCard;};
        void setkeyCard(bool x){keyCard = x;};
        void setHabilidadExtra(bool x){habilidadExtra = x;};
        void setPociones(int x){pociones = x;};
        void setArmadura(int x){armadura = x;};

        sf::Vector2f& getLastControlPoint(){return lastControlPoint;};
        void setLastControlPoint(sf::Vector2f x){lastControlPoint = x;};
    protected:
    private:
        static Ventana* instance;
        Ventana();

        int pociones;
        int armadura;
        bool habilidadExtra;
        bool keyCard;

        sf::Vector2f lastControlPoint;
        virtual ~Ventana();
};

#endif // WINDOW_H
