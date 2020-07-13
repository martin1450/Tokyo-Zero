#include "World.h"
#include "State.h"
#include <SFML/Graphics.hpp>
#include <Ventana.h>
#include "Window.h"
#include "TextoP.h"
#define UPDATE_TICK_TIME (1000/15)
World::World()
{
    //ctor
}

void World::nuevoMundo(int plantilla) {

    state.nuevaBatalla(plantilla);
}

void World::inicializar(int x)
{
    state.setEstado(x);


    ///PAUSE MENU
     if (!pauseWindowTexture.loadFromFile("resources/PauseWindow.png"))
    {
        std::cerr << "Error cargando la imagen PauseWindow.png";
        exit(0);
    }
    if (!xiconTexture.loadFromFile("resources/xicon.png"))
    {
        std::cerr << "Error cargando la imagen PauseWindow.png";
        exit(0);
    }
    if (!viconTexture.loadFromFile("resources/vicon.png"))
    {
        std::cerr << "Error cargando la imagen PauseWindow.png";
        exit(0);
    }
    pauseWindow.setTexture(pauseWindowTexture);
    xiconK.setTexture(xiconTexture);
    xiconH.setTexture(xiconTexture);
    viconK.setTexture(viconTexture);
    viconH.setTexture(viconTexture);
    xiconK.setScale(0.2, 0.2);
    xiconH.setScale(0.2, 0.2);
    viconK.setScale(0.2, 0.2);
    viconH.setScale(0.2, 0.2);

    pauseMask.setSize((sf::Vector2f(1920.f, 1056.f)));
    pauseMask.setFillColor(sf::Color(0, 0, 0, 220));

    potionTextPause = new TextoP(2);
    armorTextPause = new TextoP(2);

    ///BUCLE
    bucle();
}

void World::bucle()
{
    std::cout << "A comprobar chavales" << std::endl;
    state.comprobador();
    while (Ventana::getInstancia()->window.isOpen())
    {

        // Process events
        sf::Event event;
        while (Ventana::getInstancia()->window.pollEvent(event))
        {
            // Close window : exit
            if (event.type == sf::Event::Closed){
                Ventana::getInstancia()->window.close();
            }
            if(event.type == sf::Event::KeyPressed){
                if(event.key.code == sf::Keyboard::P && state.getEstado() == 2){
                    Ventana::getInstancia()->sonido->PlaySound(3);
                    if(!Ventana::getInstancia()->pausa){
                        Ventana::getInstancia()->pausa = true;
                    }else{
                        Ventana::getInstancia()->pausa = false;
                    }
                }
            if(event.key.code == sf::Keyboard::R && state.getEstado() == 2){
                std::cout << "eodo" << std::endl;
                state.eplat.reinicio();
            }
            if(event.key.code == sf::Keyboard::R && state.getEstado() == 4){
                std::cout << "eodo" << std::endl;
                state.eplat.reinicio();
            }
            }
        }

        if(state.getEstado() == 2){
            if(clockMov.getElapsedTime().asMilliseconds()> UPDATE_TICK_TIME){
                Ventana::getInstancia()->delta = clockMov.restart().asSeconds();
                Ventana::getInstancia()->lastpos = Ventana::getInstancia()->firstpos;
                Ventana::getInstancia()->lastposnpc = Ventana::getInstancia()->firstposnpc;

                state.controlador();
            }
        }else{
            state.controlador();
            clockMov.restart();
        }

        Ventana::getInstancia()->percent = std::min(1.f, (float)clockMov.getElapsedTime().asMilliseconds()/UPDATE_TICK_TIME);
        // Clear screen

        // Update the window
        Ventana::getInstancia()->window.clear();
        state.render();

        ///PAUSEMENU
        if(Ventana::getInstancia()->pausa){
            potionTextPause->Asignar(sf::Vector2f(Ventana::getInstancia()->cameraPosition.x+1075,  Ventana::getInstancia()->cameraPosition.y+515), std::to_string(Ventana::getInstancia()->getPociones()));
            armorTextPause->Asignar(sf::Vector2f(Ventana::getInstancia()->cameraPosition.x+1330,  Ventana::getInstancia()->cameraPosition.y+515), std::to_string(Ventana::getInstancia()->getArmadura()));
            pauseWindow.setPosition(Ventana::getInstancia()->cameraPosition.x,  Ventana::getInstancia()->cameraPosition.y);
            pauseMask.setPosition(Ventana::getInstancia()->cameraPosition.x,  Ventana::getInstancia()->cameraPosition.y);
            xiconH.setPosition(Ventana::getInstancia()->cameraPosition.x+842,  Ventana::getInstancia()->cameraPosition.y+528);
            viconH.setPosition(Ventana::getInstancia()->cameraPosition.x+842,  Ventana::getInstancia()->cameraPosition.y+528);
            xiconK.setPosition(Ventana::getInstancia()->cameraPosition.x+578,  Ventana::getInstancia()->cameraPosition.y+528);
            viconK.setPosition(Ventana::getInstancia()->cameraPosition.x+578,  Ventana::getInstancia()->cameraPosition.y+528);
            Ventana::getInstancia()->window.draw(pauseMask);
            Ventana::getInstancia()->window.draw(pauseWindow);
            Ventana::getInstancia()->window.draw(potionTextPause->getTexto());
            Ventana::getInstancia()->window.draw(armorTextPause->getTexto());
            if(Ventana::getInstancia()->getkeyCard())
                Ventana::getInstancia()->window.draw(viconK);
            else
                Ventana::getInstancia()->window.draw(xiconK);

            if(Ventana::getInstancia()->getHabilidaExtra())
                Ventana::getInstancia()->window.draw(viconH);
            else
                Ventana::getInstancia()->window.draw(xiconH);
        }

        Ventana::getInstancia()->window.display();
    }

   //return EXIT_SUCCESS;
}

void World::setState(int x)
{
    state.setEstado(x);
}


int World::getState()
{
    return state.getEstado();
}


World::~World()
{
    //dtor
}
