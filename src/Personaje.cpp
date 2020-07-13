#include <SFML/Graphics.hpp>
#include <iostream>

#include "Personaje.h"
#include "CargaSprites.h"
#include "Ecomb.h"
#include "Colorea.h"

using namespace sf;

extern bool turno;

Personaje::Personaje() {

    vida = 100;
    vidaini = vida;//almacena la vida inicial para el calculo del % de la barra
    armadura = 20;
    dano = 40;
    critico = 10;
    textura = CargaSprites::getTexture("resources/enemigo.png");
    textura2 = CargaSprites::getTexture("resources/nullataque.png");
    textura3 = CargaSprites::getTexture("resources/nullataque.png");
    textura4 = CargaSprites::getTexture("resources/VidaHUD2.png");//textura de la barra
    sprite = Sprite(textura);
    sprite.setOrigin(textura.getSize().x/2, textura.getSize().y/2);
    spriteAtaque1 = Sprite(textura2);
    spriteImpacto1 = Sprite(textura3);
    haAtacado = false;
    vivo = true;
    numCohete = 1;

    //barra vida
    spriteVida1 = Sprite(textura4);
    spriteVida1.setTextureRect(IntRect(0, 0, 512, 128));
    spriteVida2 = Sprite(textura4);
    spriteVida2.setTextureRect(IntRect(0, 128, 512, 256));
    RectangleShape rectanguloss(sf::Vector2f(229.f, 25.f));
    Colorea col(53, 250, 222);
    rectanguloss.setFillColor(col.getColor());
    marcavida = rectanguloss;

    spriteAtaque1.setScale(0.611,0.611);
    spriteImpacto1.setScale(0.51,0.51);

    spriteAtaque1.setPosition(-10, 200);
    spriteImpacto1.setPosition(-10, 243);
}

int Personaje::actuar() {

    int hit = dano-20/10;

    return hit;
}

int Personaje::habilidadNull1(){

    int hit = 40;

    return hit;
}

int Personaje::habilidadNull2(){

    int hit = dano - (rand()%20)-15;
    int crit = (rand()%critico);
    int eff = (rand()%30);

    if(crit < 10){

        hit = hit*2;
        std::cout << "Golpe critico!" << std::endl;

    }

    if(eff < 20);
        hit = -hit;

    return hit;
}

int Personaje::habilidadNull3(){

    int hit = 0;
    int eff = random()%10;

    if(eff < 9)
        hit = -5;

    return hit;
}

int Personaje::habilidadNull4(int pociones){

    if(numPocion > 0){

        numPocion--;

        if(vida < 60){

            return 40;

        }
        else{

            return 100 - vida;

        }

    }
    else{

        return 0;

    }

}

int Personaje::habilidadNull5(){

    if(numCohete > 0){

        numCohete--;
        return 50;

    }
    else{

        return 0;

    }

}

bool Personaje::getQuemado(){

    return quem;

}

bool Personaje::getHackeado(){

    return hack;

}

int Personaje::getPocion(){

    return numPocion;

}

int Personaje::getCohete(){

    return numCohete;
}

void Personaje::quemado(){

    if(contq < 3){

        quem = true;
        this->setVida(5);
        contq++;

    }
    else{

        quem = false;
        contq = 0;

    }

}

int Personaje::hackeado(){

    if(conth < 2){

        hack = true;
        conth++;
        return 20;

    }
    else{

        hack = false;
        conth = 0;
        return 0;

    }

}

void Personaje::comprobarVida() {

    if(vida <= 0) {

        vivo = false;
    }
}

bool Personaje::getVivo() {

    return vivo;
}

void Personaje::setArmadura(int armor) {

    armadura = armadura + armor;
}

void Personaje::setVida(int hit) {

    vida = vida - hit;

    //barra vida
    float q = (float)vida/vidaini;
    marcavida.setScale(sf::Vector2f(q*0.8f, 0.8f));

    comprobarVida();
}

int Personaje::getVida() {

    //std::cout << vida << std::endl;
    return vida;
}

void Personaje::setHaAtacado(bool atacado) {

    haAtacado = atacado;
}

bool Personaje::getHaAtacado() {

    return haAtacado;
}

Sprite Personaje::getSprite() {

    return sprite;
}

Sprite Personaje::getSpriteAtaque() {

    return spriteAtaque1;
}

Sprite Personaje::getSpriteImpacto() {

    return spriteImpacto1;
}

void Personaje::setPosicion(float x, float y) {

    sprite.setPosition(x, y);

    if(vidaColocada==false) {

        vidaColocada = true;
        spriteVida1.setScale(0.8, 0.8);
        spriteVida2.setScale(0.8, 0.8);
        marcavida.setScale(0.8, 0.8);
        spriteVida1.setPosition(x - 30, y - 120);
        spriteVida2.setPosition(x - 30, y - 120);
        marcavida.setPosition( x + 80, y - 100);
    }
}

Sprite Personaje::getSpriteVida1() {

    return spriteVida1;
}

Sprite Personaje::getSpriteVida2() {

    return spriteVida2;
}

RectangleShape Personaje::getMarcavida() {

    return marcavida;
}

Texture Personaje::getTextura() {

    return textura;
}

int Personaje::getArmadura() {

    return armadura;
}

int Personaje::getDano() {

    return dano;
}

int Personaje::getCritico() {

    return critico;
}

int Personaje::getNumPocion() {

    return numPocion;
}

int Personaje::getNumCohete() {

    return numCohete;
}
