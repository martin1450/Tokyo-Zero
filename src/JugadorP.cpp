#include "JugadorP.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include "World.h"
#include "Ventana.h"

using namespace std;

JugadorP::JugadorP()
{
    currentImage.x = 0;
    currentImage.y = 0;
    imageCount.x = 10;
    imageCount.y = 3;

    imageCount2.x = 10;
    imageCount2.y = 3;
    currentImage2.x = 0;
    currentImage2.y = 0;
}

void JugadorP::cargar(sf::Vector2f position)
{

        if (!playerTexture.loadFromFile("resources/spritesheet2.png")) //spritesheetBuenos
        {
            std::cerr << "Error cargando la imagen spritesheet.png";
            exit(0);
        }
        sf::Vector2u tamTextura = playerTexture.getSize();
        tamTextura.x = tamTextura.x / 10;
        tamTextura.y = tamTextura.y / 3;

        //Creamos el sprite del jugador
        boy.setTexture(playerTexture);
        boy.setOrigin(tamTextura.x/2,tamTextura.y/2);
        boy.setTextureRect(sf::IntRect(tamTextura.x * 0, tamTextura.y * 0, tamTextura.x, tamTextura.y));
        boy.setScale(0.40,0.40);
        // Lo dispongo en el centro de la pantalla
        boy.setPosition(position);

        //Ventana::getInstancia()->Ventana.getSize().y
        Ventana::getInstancia()->cameraPosition.x = boy.getPosition().x-(1920/2);
        Ventana::getInstancia()->cameraPosition.y = 0;
        Ventana::getInstancia()->camera.reset(sf::FloatRect( Ventana::getInstancia()->cameraPosition.x,  Ventana::getInstancia()->cameraPosition.y, 1920, 1056));
        Ventana::getInstancia()->firstpos = boy.getPosition();
        Ventana::getInstancia()->lastpos = boy.getPosition();

}

void JugadorP::moverse(){

sf::Vector2f movement(0.0f, 0.0f); //se cambia segun s pulsas dcha izinq etz, se va actualizando

    uvRect.width = playerTexture.getSize().x / float(imageCount.x); //iniciaiza recorte
    uvRect.height = playerTexture.getSize().y / float(imageCount.y);//ancho altura recorte

    float deltaTime = Ventana::getInstancia()->delta;

    //Leemos teclado
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A) && !sf::Keyboard::isKeyPressed(sf::Keyboard::S) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
        movement.x -= speed * deltaTime; //se mueve a la izquierda
        row = 0;
        flip = true; //que se de la vuelta
        Ventana::getInstancia()->direccion = -1; //que se de la vuelta
    }else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D) && !sf::Keyboard::isKeyPressed(sf::Keyboard::S) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
        movement.x += speed * deltaTime;
        row = 0;
        flip = false;
        Ventana::getInstancia()->direccion = 1;
    }else if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
        row = 1;
        Ventana::getInstancia()->agachado = true;
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
            movement.x -= speed * deltaTime;
            flip = true;
            Ventana::getInstancia()->direccion = -1;
        }else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
            movement.x += speed * deltaTime;
            flip = false;
            Ventana::getInstancia()->direccion = 1;
        }
    }else{
        row = 0;
        Ventana::getInstancia()->agachado = false;
    }

    comprobador();

    //Comprobamos si se ha cambiado de tecla
    if(ActualRow != row){
        currentImage.x = 0;
        ActualRow = row;
    }

    //Actualizamos animacion del sprite
    currentImage.y = row;
    if(movement.x != 0){
        totalTime += deltaTime;
        if(totalTime >= switchTime){
            totalTime -= switchTime;

            currentImage.x++;
            //Si llegamos al ultimo sprite de la animacion volvemos al principio
            if(currentImage.x >= imageCount.x-1){
                currentImage.x = 1;
            }
        }
    }else{
        currentImage.x = 0;
    }

    uvRect.top = currentImage.y * uvRect.height;
    if(flip == false){
        uvRect.left = currentImage.x * uvRect.width;
        uvRect.width = abs(uvRect.width);

    }else{
        uvRect.left = (currentImage.x + 1) * abs(uvRect.width);
        uvRect.width = -abs(uvRect.width);
    }
    /*
    //Actualizamos el uvRect con la nueva x e y
    uvRect.left = currentImage.x * uvRect.width;
    uvRect.top = currentImage.y * uvRect.height;
    */
    //Actualizamos el recorte de texture del sprite
    boy.setTextureRect(uvRect);


    //Movemos sprite

    //Ventana::getInstancia()->firstpos += movement;
    if(!Ventana::getInstancia()->caida){
        Ventana::getInstancia()->firstpos += movement;
    }
}

void JugadorP::comprobador(){
   int jugadorX = 0;
   sf::FloatRect shapeBoy = boy.getGlobalBounds();
   if(Ventana::getInstancia()->direccion == -1){
       jugadorX = boy.getPosition().x;
   }else{
       jugadorX = boy.getPosition().x;
   }
   int jugadorY = boy.getPosition().y - shapeBoy.width/2;
    int tileX = floor(jugadorX/32);
    int tileY = floor(jugadorY/32);
    int tile = ((tileY-1)*120+tileX)-1;

   if(Ventana::getInstancia()->colisones[tile] == 11598){
        row = 1;
        Ventana::getInstancia()->agachado = true;
   }
}
void JugadorP::jump(){

    sf::Vector2f movement(0.0f, 0.0f); //se cambia segun s pulsas dcha izq etz, se va actualizando
    float deltaTime = Ventana::getInstancia()->delta;


    if(!isJumping){
        playerVelocity.x = 0;
        playerVelocity.y = 0;
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && !isJumping){
        playerVelocity.y=-jumpSpeed;
        isJumping=true;
        cayendo = false;
        subiendo = true;
        currentImage2.x = 0;

        Ventana::getInstancia()->sonido->PlaySound(4);
    }
    if(isJumping){
        playerVelocity.y+=(gravity*deltaTime);
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
            playerVelocity.x -= jumpscrollspeed * deltaTime;
            flip = true;
        }else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            playerVelocity.x += jumpscrollspeed * deltaTime;
            flip = false;
        }

        if(playerVelocity.y > 0){
            cayendo = true;
            subiendo = false;
        }
    }

    currentImage2.y = 2;
    totalTime2 += deltaTime;

    if(totalTime2 >= switchTime){
        totalTime2 -= switchTime;
        if(currentImage2.x < imageCount2.x-5)
            currentImage2.x++;
        //Si llegamos al ultimo sprite de la animacion volvemos al principio

        if(currentImage2.x >= imageCount2.x-5){
            currentImage2.x = imageCount2.x-6;
        }
    }

    uvRect.top = currentImage2.y * uvRect.height;
    if(flip == false){
        uvRect.left = currentImage2.x * uvRect.width;
        uvRect.width = abs(uvRect.width);
    }else{
        uvRect.left = (currentImage2.x + 1) * abs(uvRect.width);
        uvRect.width = -abs(uvRect.width);
    }

    boy.setTextureRect(uvRect);

    //boy.move(playerVelocity*deltaTime);
    movement=playerVelocity*deltaTime;
    Ventana::getInstancia()->firstpos += movement;

}


bool JugadorP::EntrarEnVortice(){
    bool entrado = false;
    entrandoEnVortice = true;
    if(entrandoEnVortice){
        contadorVortice += Ventana::getInstancia()->delta;
        boy.setRotation(boy.getRotation()+5.0);
        boy.setScale(boy.getScale().x-0.1*Ventana::getInstancia()->delta, boy.getScale().y-0.1*Ventana::getInstancia()->delta);
        boy.setPosition(boy.getPosition().x,boy.getPosition().y-18.0);
        if(contadorVortice > 3.0){
            entrado = true;
        }
    }

    if(entrado){
        boy.setRotation(0);
        boy.setScale(0.40,0.40);
        contadorVortice = 0;
        entrandoEnVortice = false;
    }

    return entrado;
}


JugadorP::~JugadorP()
{
    //dtor
}
