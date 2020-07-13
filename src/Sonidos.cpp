#include "Sonidos.h"
#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;

Sonidos::Sonidos()
{
    if (!agujeroBuffer.loadFromFile("resources/Sounds/agujero.wav")){
        std::cerr << "Error cargando el sonido";
            exit(0);
    }
    if (!keyBuffer.loadFromFile("resources/Sounds/key.wav")){
        std::cerr << "Error cargando el sonido";
            exit(0);
    }
    if (!puertaBuffer.loadFromFile("resources/Sounds/puerta.wav")){
        std::cerr << "Error cargando el sonido";
            exit(0);
    }
    if (!pauseBuffer.loadFromFile("resources/Sounds/pause.wav")){
        std::cerr << "Error cargando el sonido";
            exit(0);
    }
    if (!jumpBuffer.loadFromFile("resources/Sounds/jump.wav")){
        std::cerr << "Error cargando el sonido";
            exit(0);
    }
    if (!powerUpBuffer.loadFromFile("resources/Sounds/powerUp.wav")){
        std::cerr << "Error cargando el sonido";
            exit(0);
    }
     if (!menuBuffer.loadFromFile("resources/Sounds/misc_menu_4.wav")){
        std::cerr << "Error cargando el sonido";
            exit(0);
    }
    if (!fuenteBuffer.loadFromFile("resources/Sounds/aura.wav")){
        std::cerr << "Error cargando el sonido";
            exit(0);
    }
    if (!katanaBuffer.loadFromFile("resources/Sounds/katana1.wav")){
        std::cerr << "Error cargando el sonido";
            exit(0);
    }
    katanaSound.setBuffer(katanaBuffer);
    if (!disparoBuffer.loadFromFile("resources/Sounds/disparofuturista.wav")){
        std::cerr << "Error cargando el sonido";
            exit(0);
    }
    disparoSound.setBuffer(disparoBuffer);
    if (!hackeoBuffer.loadFromFile("resources/Sounds/hackeo1.wav")){
        std::cerr << "Error cargando el sonido";
            exit(0);
    }
    hackeoSound.setBuffer(hackeoBuffer);
    if (!inyeccionBuffer.loadFromFile("resources/Sounds/pocion.wav")){
        std::cerr << "Error cargando el sonido";
            exit(0);
    }
    inyeccionSound.setBuffer(inyeccionBuffer);
    if (!ultiBuffer.loadFromFile("resources/Sounds/misile.wav")){
        std::cerr << "Error cargando el sonido";
            exit(0);
    }
    ultiSound.setBuffer(ultiBuffer);
    if (!enemigosBuffer.loadFromFile("resources/Sounds/enemigos2.wav")){
        std::cerr << "Error cargando el sonido";
            exit(0);
    }
    enemigosSound.setBuffer(enemigosBuffer);
    if (!seleccionenemigosBuffer.loadFromFile("resources/Sounds/seleccionEnemigos.wav")){
        std::cerr << "Error cargando el sonido";
            exit(0);
    }
    seleccionenemigosSound.setBuffer(seleccionenemigosBuffer);
    if (!loadBuffer.loadFromFile("resources/Sounds/load.wav")){
        std::cerr << "Error cargando el sonido";
            exit(0);
    }
    loadSound.setBuffer(loadBuffer);

    fuenteSound.setBuffer(fuenteBuffer);

    powerUpSound.setBuffer(powerUpBuffer);
    jumpSound.setBuffer(jumpBuffer);
    pauseSound.setBuffer(pauseBuffer);
    puertaSound.setBuffer(puertaBuffer);
    keySound.setBuffer(keyBuffer);
    agujeroSound.setBuffer(agujeroBuffer);
    menuSound.setBuffer(menuBuffer);
}

void Sonidos::crear(sf::String cadena){
    if (!buffer.loadFromFile(cadena)){
        std::cerr << "Error cargando el sonido";
            exit(0);
    }

    sound.setBuffer(buffer);
    sound.setLoop(true);
}

void Sonidos::sonar(){
    sound.play();
}

void Sonidos::pausar(){
    sound.pause();
}

void Sonidos::PlaySound(int x){
    switch(x){
        case 0:
        {
            agujeroSound.stop();
            agujeroSound.play();
            break;
        }
        case 1:
        {
            keySound.stop();
            keySound.play();
            break;
        }
        case 2:
        {
            puertaSound.stop();
            puertaSound.play();
            break;
        }
        case 3:
        {
            pauseSound.stop();
            pauseSound.play();
            break;
        }
        case 4:
        {
            jumpSound.stop();
            jumpSound.play();
            break;
        }
        case 5:
        {
            powerUpSound.stop();
            powerUpSound.play();
            break;
        }
        case 6:
        {
            menuSound.stop();
            menuSound.play();
            break;
        }
        case 7:
        {
            fuenteSound.stop();
            fuenteSound.play();
            break;
        }
        case 8:
        {
            katanaSound.stop();
            katanaSound.play();
            break;
        }
        case 9:
        {
            disparoSound.stop();
            disparoSound.play();
            break;
        }
        case 10:
        {
            inyeccionSound.stop();
            inyeccionSound.play();
            break;
        }
        case 11:
        {
            hackeoSound.stop();
            hackeoSound.play();
            break;
        }
        case 12:
        {
            ultiSound.stop();
            ultiSound.play();
            break;
        }
        case 13:
        {
            enemigosSound.stop();
            enemigosSound.play();
            break;
        }
        case 14:
        {
            seleccionenemigosSound.stop();
            seleccionenemigosSound.play();
            break;
        }
        case 15:
        {
            loadSound.stop();
            loadSound.play();
            break;
        }
    }
}

Sonidos::~Sonidos()
{
    //dtor
}
