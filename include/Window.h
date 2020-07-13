#ifndef WINDOW_H
#define WINDOW_H
#include "World.h"
#include <SFML/Graphics.hpp>

class Window
{
    public:
        static Window* getInstancia();
        float delta = 0.0f;
        float percent=0.0f;
        World world;
        sf::RenderWindow window;
        sf::Vector2f firstpos;
        sf::Vector2f lastpos;
        static sf::Texture& getTexture(std::string const& archivo);

    protected:
    private:
        static Window* instance;
        Window();
        std::map <std::string, sf::Texture> m_Texturas;
        virtual ~Window();

};

#endif // WINDOW_H
