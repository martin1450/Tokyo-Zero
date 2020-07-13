#include "Npc.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include "World.h"
#include "Ventana.h"


Npc::Npc()
{
    currentImage1.x = 0;
    currentImage1.y = 0;
    imageCount1.x = 4;
    imageCount1.y = 3;
}

void Npc::cargar(sf::Vector2f posicion, int tipoEnemigos){

        switch(tipoEnemigos){
        case 1:
            {
                if (!enemigosTexture.loadFromFile("resources/enemigos3.png"))
                {
                    std::cerr << "Error cargando la imagen enemigos3.png";
                    exit(0);
                }
                break;
            }
        case 2:
            {
                if (!enemigosTexture.loadFromFile("resources/enemigo.png"))
                {
                    std::cerr << "Error cargando la imagen enemigo.png";
                    exit(0);
                }
                break;
            }
    }

        sf::Vector2u tamTextura = enemigosTexture.getSize();
        tamTextura.x = tamTextura.x / 6;
        tamTextura.y = tamTextura.y / 3;

        //Creamos el sprite del jugador
        enemigos.setTexture(enemigosTexture);
        enemigos.setOrigin(tamTextura.x/2,tamTextura.y/2);
        enemigos.setTextureRect(sf::IntRect(tamTextura.x * 0, tamTextura.y * 0, tamTextura.x, tamTextura.y));
        enemigos.setScale(0.35,0.35); //1,2
        // Lo dispongo en el centro de la pantalla
        enemigos.setPosition(posicion);
        Ventana::getInstancia()->firstposnpc = enemigos.getPosition();
        Ventana::getInstancia()->lastposnpc = Ventana::getInstancia()->firstposnpc;
        luchado = false;
        tipo = tipoEnemigos;

}

void Npc::setPosicionInicial(sf::Vector2f posicion){
    posini=posicion;
    Ventana::getInstancia()->firstposnpc = posini;
    Ventana::getInstancia()->lastposnpc = Ventana::getInstancia()->firstposnpc;
}
void Npc::movimiento(){


    sf::Vector2f movimiento(0.0f, 0.0f); //se cambia segun s pulsas dcha izinq etz, se va actualizando

    uvRect.width = enemigosTexture.getSize().x / float(imageCount1.x); //iniciaiza recorte
    uvRect.height = enemigosTexture.getSize().y / float(imageCount1.y);//ancho altura recorte

    float deltaTime = Ventana::getInstancia()->delta;

    if(cambio==false){
        movimiento.x+=speed*deltaTime;
        flip=true;
    }else{
        movimiento.x-=speed*deltaTime;
        flip=false;
    }
    /*if(movimiento.x>3){
        cout << "mayor: " << movimiento.x << endl;
        flip=false;
    }else if (movimiento.x<3){
        cout << "menor: " << movimiento.x << endl;
        flip=true;
    }*/

    /*if(movimiento.x != 0){
        totalTime += deltaTime;
        if(totalTime >= switchTime){
            totalTime -= switchTime;
            currentImage1.x++;
            //Si llegamos al ultimo sprite de la animacion volvemos al principio
            if(currentImage1.x >= imageCount1.x-1){
                currentImage1.x = 0;
            }
        }
    }*/


    if(movimiento.x != 0){
        totalTime += deltaTime;
        if(totalTime >= switchTime){
            totalTime -= switchTime;
            currentImage1.x++;
            //Si llegamos al ultimo sprite de la animacion volvemos al principio
            cout << "current image x: " << currentImage1.x <<  endl;
            if(currentImage1.x >= imageCount1.x){
                currentImage1.x = 0;
                currentImage1.y++;

                cout << "current image y: " << currentImage1.y <<  endl;
                if(currentImage1.y==3){
                    currentImage1.x = 0;
                    currentImage1.y=0;
                }
            }

        }
    }


    uvRect.top = currentImage1.y * uvRect.height;
    if(flip == false){
        uvRect.left = currentImage1.x * uvRect.width;
        uvRect.width = abs(uvRect.width);

    }else{
        uvRect.left = (currentImage1.x + 1) * abs(uvRect.width);
        uvRect.width = -abs(uvRect.width);
    }

    enemigos.setTextureRect(uvRect);
    Ventana::getInstancia()->firstposnpc += movimiento;

}


Npc::~Npc()
{

}
