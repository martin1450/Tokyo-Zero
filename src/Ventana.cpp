#include "Ventana.h"
#include <SFML/Graphics.hpp>

Ventana* Ventana::instance = nullptr;

Ventana* Ventana::getInstancia(){
        if(instance == nullptr)
            instance = new Ventana();

        return instance;
}
    //sf::RenderWindow window2(sf::VideoMode(1920, 1056), "Tokyo Zero", sf::Style::Close | sf::Style::Resize);

Ventana::Ventana()
{
     tamX = 1920;
     tamY = 1056;
     //window.create(sf::VideoMode(1920, 1056), "Tokyo Zero", sf::Style::Close | sf::Style::Resize);
     window.create(sf::VideoMode(tamX, tamY), "Tokyo Zero", sf::Style::Close | sf::Style::Resize);
     window.setFramerateLimit(60);
     firstpos.x = 0.0f;
     firstpos.y = 0.0f;
     cameraPosition.x = 0.0f;
     cameraPosition.y = 0.0f;
     camera.setViewport(sf::FloatRect(0,0,1.0f,1.0f));
     firstposnpc.x = 0.0f;
     firstposnpc.y = 0.0f;
     sonido=new Sonidos;
     updates = 15;
    Ventana::getInstancia()->finTexture.loadFromFile("resources/final.png");
    Ventana::getInstancia()->fin.setTexture(Ventana::getInstancia()->finTexture);
    Ventana::getInstancia()->fin.setOrigin(1920/2,1080/2);
    Ventana::getInstancia()->fin.setPosition(1920/2, 1056/2);

}

Ventana::~Ventana()
{
    delete instance;
}
