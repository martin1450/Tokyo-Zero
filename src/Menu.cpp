#include "Menu.h"
#include "Ventana.h"
#include "World.h"
#include "State.h"
#include "CargaSprites.h"
#include <string>

Menu::Menu()
{

    x = 1920;
    y = 1080;
    //Colorea col(192, 0, 255);
    Colorea col(255, 0, 187);


    Texto iniciarSec(true, col, "INICIAR", 210, 670, 58); //X/2, Y/4
    texto[0] = iniciarSec;
    col.setColor(2, 184, 255);
                //Ventana::getInstancia()->sonido->PlaySound(6);

    //Texto iniciar(true, col, "INICIAR", 210 - 7, 670 - 4, 50); //Y/4-4
    //texto[1] = iniciar;

    //Texto opciones(true, col, "CONTROLES", 210 - 7, 870 - 4, 50); //Y/4*2-4
    //texto[2] = opciones;
    //Texto salir(true, col, "SALIR", x/2 - 7, 670 - 4, 50);//Y/4*3-4
    //texto[3] = salir;

    seleccionado = 1;
    aux = false;

    //sf::Texture textura = CargaSprites::getTexture("resources/fondo.png");

    //textura.loadFromFile("resources/fondo.png");
    spriteFondo = sf::Sprite(CargaSprites::getTexture("resources/fondo2.jpg"));


    if (!controlesTexture.loadFromFile("resources/controles.png")) //spritesheetBuenos
        {
            std::cerr << "Error cargando la imagen controles.png";
            exit(0);
        }

        controles.setTexture(controlesTexture);
        transparencia.setSize((sf::Vector2f(1920.f, 1080.f)));
        transparencia.setFillColor(sf::Color(0, 0, 0, 220));

}

Menu::~Menu()
{
    //dtor
}

std::array<Texto, numMaxItems>* Menu::getTextos()
{

    return &texto;

}

void Menu::mUp()
{

    if(seleccionado - 1 >= 1)
    {

        if (seleccionado == 2)
        {
            texto[0].setContenido("INICIAR");
            texto[0].setPosicion(210, 670);
            seleccionado--;
            Ventana::getInstancia()->sonido->PlaySound(6);

        }

        else if (seleccionado == 3)
        {
            texto[0].setContenido("CONTROLES");
            texto[0].setPosicion(210, 775); // x/2, y/4*2
            seleccionado--;
            Ventana::getInstancia()->sonido->PlaySound(6);

        }

    }

}

void Menu::mDown()
{

    if(seleccionado + 1 < numMaxItems)
    {
        if (seleccionado == 1)
        {
            texto[0].setContenido("CONTROLES");
            texto[0].setPosicion(210, 775);//x/2, y/4*2
            seleccionado++;
            Ventana::getInstancia()->sonido->PlaySound(6);

        }

        else if (seleccionado == 2)
        {
            texto[0].setContenido("SALIR");
            texto[0].setPosicion(210, 875);//x/2, y/4*3
            seleccionado++;
                        Ventana::getInstancia()->sonido->PlaySound(6);

        }

    }

}

int Menu::botonPresionado()
{

    return seleccionado;

}

void Menu::procesEvent() {

    //std::cout << aux << std::endl;
    //std::cout << "eventeando" << std::endl;
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && aux == false && dibujarControles == false) {

        aux = true;
        mUp();
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && aux == false && dibujarControles == false) {

        aux = true;
        mDown();
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return) && dibujarControles == false) {

        if(botonPresionado() == 1)
        {
            std::cout << Ventana::getInstancia() -> world.getState() << std::endl;
            Ventana::getInstancia() -> world.setState(2);
            eplat.sonarSonidos();
            std::cout << Ventana::getInstancia() -> world.getState() << std::endl;
            //state.setEstado(2);

        }

        if(botonPresionado() == 2)
        {
            dibujarControles = true;
            //Window::getInstancia() ->
        }

        if(botonPresionado() == 3)
        {

            Ventana::getInstancia()->window.close();
            //Window::getInstancia() ->

        }
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
        dibujarControles = false;
    }

    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up) == false && sf::Keyboard::isKeyPressed(sf::Keyboard::Down) == false) {

        aux = false;
    }
}


/*
    while(Ventana::getInstancia()->window.pollEvent(eventoGame)) {
        std::cout << "eventeando" << std::endl;
        switch(eventoGame.type)
        {

        case sf::Event::KeyReleased:

            switch (eventoGame.key.code)
            {

                case sf::Keyboard::Up:
                    mUp();
                    break;

                case sf::Keyboard::Down:
                    mDown();
break;

                case sf::Keyboard::Return:
                    if(botonPresionado() == 1)
                    {
                        std::cout << Ventana::getInstancia() -> world.getState() << std::endl;
                        Ventana::getInstancia() -> world.setState(2);
                        std::cout << Ventana::getInstancia() -> world.getState() << std::endl;
                        //state.setEstado(2);

                    }

                    if(botonPresionado() == 3)
                    {

                        Ventana::getInstancia()->window.close();
                        //Window::getInstancia() ->

                    }
                    break;

                default: break;

            }

        break;

        default: break;

        }

    }
*/

void Menu::dibujar()
{
    //Ventana::getInstancia()->window.clear();

    Ventana::getInstancia()->window.draw(spriteFondo);
    Ventana::getInstancia()->window.draw(sprite2);

    Ventana::getInstancia()->window.draw(texto[0].getTexto());
    Ventana::getInstancia()->window.draw(texto[1].getTexto());
    Ventana::getInstancia()->window.draw(texto[2].getTexto());
    Ventana::getInstancia()->window.draw(texto[3].getTexto());

    if(dibujarControles){

        Ventana::getInstancia()->window.draw(transparencia);
        Ventana::getInstancia()->window.draw(controles);

    }

    //Ventana::getInstancia()->window.display();
}

void Menu::muestraV()
{

   // while (Ventana::getInstancia()->window.isOpen() && Ventana::getInstancia() -> world.getState()==1)
   // {

        procesEvent();
        dibujar();

   // }

}
