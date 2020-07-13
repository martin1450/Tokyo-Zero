#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <cstdlib>

#include "Ecomb.h"
#include "CargaSprites.h"
#include "Personaje.h"
#include "AnimaSprites.h"
#include "Ventana.h"

using namespace sf;

bool turno = true;

Ecomb::Ecomb(int plantilla) {

    std::cout << "Ecomb: " << plantilla << std::endl;
    numenem = 2;
    hackeo = -1;
    plant = plantilla;

    std::cout << "pociones: " << pociones << std::endl;
    std::cout << "misiles: " << ulti << std::endl;
    if(Ventana::getInstancia()->getPociones() < 10 && Ventana::getInstancia()->getPociones() >= 0) {

        pociones = Ventana::getInstancia()->getPociones();
    }
    if(Ventana::getInstancia()->getHabilidaExtra() == true) {

        ulti = 1;
    }
    else {

        ulti = 0;
    }
    cargarGraficos(plantilla);
    //bucleJuego();
}

void Ecomb::lanzarAtaque(sf::Sprite &spriteAtaque, sf::Sprite &spriteImpacto, bool nullAtaca) {

    Ventana::getInstancia() -> window.clear();

    // DIBUJADO
    Ventana::getInstancia() -> window.draw(fondoCombate);

    for(int i=0; i<3; i++) {

        if(enemigos[i] != NULL && enemigos[i]->getVivo() == true) {

            Ventana::getInstancia() -> window.draw(enemigos[i]->getSprite());
        }
    }

    // ANIMACIONES
    Ventana::getInstancia() -> window.draw(nullSprite);
    //animaNull -> animar();
    //Ventana::getInstancia() -> window.draw(*nullSprite);

    // CARGAR TEXTO
    cargarTextos();

    // DIBUJAR HUD
    Ventana::getInstancia() -> window.draw(hud);
    for(int i=0; i<3; i++) {
        Ventana::getInstancia() -> window.draw(habilidades[i]);
    }

    //Dibijando stats de null
    Ventana::getInstancia() -> window.draw(statsnull);
    Ventana::getInstancia() -> window.draw(indicadorVidaNull);
    Ventana::getInstancia() -> window.draw(indicadorDanoNull);
    Ventana::getInstancia() -> window.draw(indicadorArmaduraNull);
    Ventana::getInstancia() -> window.draw(indicadorCriticoNull);
    Ventana::getInstancia() -> window.draw(numPocion);
    Ventana::getInstancia() -> window.draw(numCohete);

    //Dibujando stats enemigo
    /*if(dibujaenemi != -1) {
        Ventana::getInstancia() -> window.draw(vidas[dibujaenemi]);
    }*/

    if(opacidadFade <= 170) {

        opacidadFade += 2;
        fade.setColor(Color(255, 255, 255, opacidadFade));
    }
    Ventana::getInstancia() -> window.draw(fade);

    if(nullAtaca == true) {

        Ventana::getInstancia() -> window.draw(fondob);
    }
    else {

        Ventana::getInstancia() -> window.draw(fondom);
    }

    Ventana::getInstancia() -> window.draw(spriteAtaque);
    Ventana::getInstancia() -> window.draw(spriteImpacto);

    if(nullAtaca == true) {

        spriteAtaque.move(velocidadAtaque*2, 0);
        spriteImpacto.move(-velocidadAtaque, 0);
    }
    else {

        spriteAtaque.move(velocidadAtaque, 0);
        spriteImpacto.move(-velocidadAtaque*2, 0);
    }
    spriteAtaque.setColor(Color (255, 255, 255, opacidad));
    spriteImpacto.setColor(Color (255, 255, 255, opacidad));

    if (velocidadAtaque < 0.2 && opacidad-2 >= 0) {

        opacidad -= 2;
    }
    velocidadAtaque -= velocidadAtaque/60;

    Ventana::getInstancia() -> window.display();
}

void Ecomb::combatir() {

    Ventana::getInstancia() -> window.draw(fondoCombate);

    std::cout << plant << std::endl;

    // COMPROBAR Y DIBUJAR ENEMIGOS
    for(int i=0; i<3; i++) {

        if(enemigos[i] != NULL && enemigos[i]->getVivo() == false) {        // SI ACABA DE MORIR, LO HACE NULL
            std::cout << "Me voy a poner a null" << std::endl;

            hackeo = -1;
            enemigos[i] = NULL;
            numenem--;
            std::cout << "Ahora soy null" << std::endl;
        }
        else if(enemigos[i] != NULL && enemigos[i]->getVivo() == true) {    // SI ESTA VIVO, LO DIBUJA

            if(i==0) {

                if(enemigos[0]->getSprite().getPosition().y > 290 && direccion1==true) {

                    enemigos[0]->setPosicion(enemigos[0]->getSprite().getPosition().x, enemigos[0]->getSprite().getPosition().y-0.1);
                }
                else if(enemigos[0]->getSprite().getPosition().y < 300){

                    direccion1 = false;
                    enemigos[0]->setPosicion(enemigos[0]->getSprite().getPosition().x, enemigos[0]->getSprite().getPosition().y+0.1);
                }
                else {

                    direccion1 = true;
                }
            }
            else if(i==1) {

                if(enemigos[1]->getSprite().getPosition().y > 290 && direccion2==true) {

                    enemigos[1]->setPosicion(enemigos[1]->getSprite().getPosition().x, enemigos[1]->getSprite().getPosition().y-0.05);
                }
                else if(enemigos[1]->getSprite().getPosition().y < 300){

                    direccion2 = false;
                    enemigos[1]->setPosicion(enemigos[1]->getSprite().getPosition().x, enemigos[1]->getSprite().getPosition().y+0.05);
                }
                else {

                    direccion2 = true;
                }
            }
            else {

                if(enemigos[2]->getSprite().getPosition().y > 290 && direccion3==true) {

                    enemigos[2]->setPosicion(enemigos[2]->getSprite().getPosition().x, enemigos[2]->getSprite().getPosition().y-0.08);
                }
                else if(enemigos[2]->getSprite().getPosition().y < 300){

                    direccion3 = false;
                    enemigos[2]->setPosicion(enemigos[2]->getSprite().getPosition().x, enemigos[2]->getSprite().getPosition().y+0.08);
                }
                else {

                    direccion3 = true;
                }
            }
            Ventana::getInstancia() -> window.draw(enemigos[i]->getSprite());
            Ventana::getInstancia() -> window.draw(enemigos[i]->getSpriteVida2());
            Ventana::getInstancia() -> window.draw(enemigos[i]->getMarcavida());
            Ventana::getInstancia() -> window.draw(enemigos[i]->getSpriteVida1());
            Ventana::getInstancia() -> window.draw(vidas[i]);

            Ventana::getInstancia() -> window.draw(nullCombate->getSpriteVida2());
            Ventana::getInstancia() -> window.draw(nullCombate->getMarcavida());
            Ventana::getInstancia() -> window.draw(nullCombate->getSpriteVida1());

        }
    }
    if(nullSprite.getPosition().y > 290 && direccion0==true) {

        nullSprite.move(0, -0.05);
    }
    else if(nullSprite.getPosition().y < 300){

        direccion0 = false;
        nullSprite.move(0, 0.05);
    }
    else {

        direccion0 = true;
    }

    // EFECTOS
    if(enemigos[0] != NULL && enemigos[0]->getQuemado()){

        Ventana::getInstancia() -> window.draw(quem1);
    }
    if(enemigos[1] != NULL && enemigos[1]->getQuemado()){

        Ventana::getInstancia() -> window.draw(quem2);
    }
    if(enemigos[0] != NULL && enemigos[0]->getHackeado() && numenem > 1){

        Ventana::getInstancia() -> window.draw(hack1);
    }
    if(enemigos[1] != NULL && enemigos[1]->getHackeado() && numenem > 1){

        Ventana::getInstancia() -> window.draw(hack2);
    }

    if(nullCombate->getVivo() == false && modoDios == false) {

        //Ventana::getInstancia() -> world.state.eplat.reinicio();
        Ventana::getInstancia() -> world.setState(1);
        std::cout << "Estoy muerto" << std::endl;
    }

    // ANIMAR SPRITES
    Ventana::getInstancia() -> window.draw(nullSprite);
    //animaNull -> animar();
    //Ventana::getInstancia() -> window.draw(*nullSprite);

    // CARGAR TEXTO
    cargarTextos();

    // DIBUJAR HITBOXES
    for(int i=0; i<3; i++) {

        if (enemigos[i] != NULL && enemigoElegido == i) {

            posiciones[i].rotate(0.8);
            Ventana::getInstancia() -> window.draw(posiciones[i]);
        }
    }
    //std::cout << "Check" << std::endl;
    // DIBUJAR HUD
    Ventana::getInstancia() -> window.draw(hud);
    for(int i=0; i<5; i++) {
        Ventana::getInstancia() -> window.draw(habilidades[i]);
    }
    Ventana::getInstancia() -> window.draw(textohabilidad);

    //Dibijando stats de null
    Ventana::getInstancia() -> window.draw(statsnull);
    Ventana::getInstancia() -> window.draw(indicadorVidaNull);
    Ventana::getInstancia() -> window.draw(indicadorDanoNull);
    Ventana::getInstancia() -> window.draw(indicadorArmaduraNull);
    Ventana::getInstancia() -> window.draw(indicadorCriticoNull);
    Ventana::getInstancia() -> window.draw(numPocion);
    Ventana::getInstancia() -> window.draw(numCohete);

    //Dibujando stats enemigo
    if(dibujaenemi != -1) {
        Ventana::getInstancia() -> window.draw(statsenemy);
        Ventana::getInstancia() -> window.draw(vidas[dibujaenemi]);
        Ventana::getInstancia() -> window.draw(dano[dibujaenemi]);
        Ventana::getInstancia() -> window.draw(armadura[dibujaenemi]);
        Ventana::getInstancia() -> window.draw(critico[dibujaenemi]);
    }

    // TURNO ENEMIGO
    if (relojAtaque.getElapsedTime().asSeconds() > 2.0f && turno == false) {

        // COMPROBAR SI HEMOS GANADO
        int muertos = 0;

        for(int i=0; i<3; i++) {

            if(enemigos[i]==NULL) {

                muertos++;
            }
        }
        if(muertos==3 && plant==4) {

            Ventana::getInstancia() -> world.setState(4);
            atacante = NULL;
        }
        else if(muertos==3) {

            Ventana::getInstancia() -> world.setState(2);
            eplat.sonarSonidos();
            atacante = NULL;
        }

        // ELEGIR ATACANTE
        elegirAtacante();

        if(atacante != NULL) {

            Clock relojSpriteAtaque;
            Sprite spriteAtaque = atacante->getSpriteAtaque();
            Sprite spriteImpacto = nullCombate->getSpriteImpacto();

            if(atacante->getQuemado()){

                atacante->quemado();
            }
            if(atacante->getHackeado()){

                if(hackeo == -1 && numenem > 1){

                    for(int i = 0 ; i < 3 ; i++){

                        if(enemigos[i] != NULL && enemigos[i] == atacante){

                            hackeo = i;

                            break;
                        }
                    }
                }

                if(atacante == enemigos[hackeo]){

                    for(int i = 0 ; i < 3 ; i++){

                        if(enemigos[i] != NULL && enemigos[i] != atacante){

                            enemigos[i]->setVida(atacante->hackeado());

                            spriteImpacto = enemigos[i]->getSpriteImpacto();

                            spriteImpacto.setPosition(100,200);

                            Ventana::getInstancia()->sonido->PlaySound(13);

                            while (relojSpriteAtaque.getElapsedTime().asSeconds() < 4.5f) {

                                // LANZAR ATAQUE
                                lanzarAtaque(spriteImpacto, spriteAtaque, false);
                            }
                        }
                    }
                }
                else{

                    nullCombate->setVida(atacante->actuar());
                    Ventana::getInstancia()->sonido->PlaySound(13);

                    while (relojSpriteAtaque.getElapsedTime().asSeconds() < 4.5f) {

                        // LANZAR ATAQUE
                        lanzarAtaque(spriteImpacto, spriteAtaque, false);
                    }
                }
            }
            else{

                nullCombate->setVida(atacante->actuar());
                Ventana::getInstancia()->sonido->PlaySound(13);

                while (relojSpriteAtaque.getElapsedTime().asSeconds() < 4.5f) {

                    // LANZAR ATAQUE
                    lanzarAtaque(spriteImpacto, spriteAtaque, false);

                }
            }
            resetearValores(true);
            relojAtaque.restart();
        }
    }
}

void Ecomb::resetearValores(bool pasaTurno) {

    velocidadAtaque = 3;
    opacidad = 255;
    opacidadFade = 1;
    turno = pasaTurno;
}

void Ecomb::elegirAtacante() {

    bool elegido = false;

    for(int i=0; i<3 && elegido==false; i++) {

        if(enemigos[i] != NULL && enemigos[i]->getHaAtacado() == false) {   // Elige atacante

            atacante = enemigos[i];
            enemigos[i]->setHaAtacado(true);
            std::cout << i << std::endl;
            elegido = true;
        }

        if(i == 2 && elegido == false) { // Si llega al final y no ha elegido atacante

            bool acabado = true;

            for(int i=0; i<3; i++) {

                if(enemigos[i] != NULL) {     // Si una posicion no es null

                    std::cout << "RESETANDO TURNOS" << std::endl;
                    enemigos[i]->setHaAtacado(false);             // Reseteamos turnos
                    acabado = false;                              // El combate no ha acabado

                    for(int j=0; j<3 && elegido==false; j++) {

                        if(enemigos[j] != NULL && enemigos[j]->getHaAtacado() == false) {   // Elige atacante

                            atacante = enemigos[j];
                            enemigos[j]->setHaAtacado(true);
                            std::cout << j << std::endl;
                            elegido = true;
                        }
                    }
                }
            }

            if(acabado == true && plant==4) {               // Si ha acabado el combate

                std::cout << "STATE 4" << std::endl;
                Ventana::getInstancia() -> world.setState(4);
                atacante = NULL;
            }
            else if(acabado == true) {

                std::cout << "COMBATE FINALIZADO" << std::endl;
                Ventana::getInstancia() -> world.setState(2);
                eplat.sonarSonidos();
                atacante = NULL;
            }
        }
    }
}

void Ecomb::cargarGraficos(int plantilla) {

    std::cout << "plantilla: " << plantilla << std::endl;

    // LOAD FUENTE
    //fuenteCursiva.loadFromFile("resources/quantummalicedropital.ttf");
	fuente.loadFromFile("resources/quantummalicedrop.ttf");

    // CARGAR HUD Y FONDO
    fondoCombate = Sprite(CargaSprites::getTexture("resources/fondo1.png"));
    std::cout << fondoCombate.getTexture()->getSize().x << std::endl;
    //fondoCombate.setScale(((float)Ventana::getInstancia()->getSize().x / fondoCombate.getTexture()->getSize().x), ((float)ventana->getSize().y / fondoCombate.getTexture()->getSize().y));  // FONDO RESPONSIVE
    hud = sf::Sprite(CargaSprites::getTexture("resources/HUD3.png"));

    // CREAR PERSONAJES
    nullCombate = new Personaje();
    nullCombate->setPosicion(400, 300);
    nullSprite = Sprite(CargaSprites::getTexture("resources/nullataque.png"));

    if(plantilla==1) {

        enemigos[0] = new Soldado();
        enemigos[0]->setPosicion(950, 300);
        enemigos[1] = new Soldado();
        enemigos[1]->setPosicion(1200, 300);
        enemigos[2] = NULL;
    }
    else if(plantilla==2) {

        enemigos[0] = new Soldado();
        enemigos[0]->setPosicion(950, 300);
        enemigos[1] = new Soldado();
        enemigos[1]->setPosicion(1200, 300);
        enemigos[2] = new Mutante();
        enemigos[2]->setPosicion(1450, 300);
    }
    else if(plantilla==3) {

        enemigos[0] = new Mutante();
        enemigos[0]->setPosicion(950, 300);
        enemigos[1] = new Soldado();
        enemigos[1]->setPosicion(1200, 300);
        enemigos[2] = NULL;
    }
    else if(plantilla==4) {

        enemigos[0] = new Zero();
        enemigos[0]->setPosicion(1200, 300);
        enemigos[1] = NULL;
        enemigos[2] = NULL;
    }

    nullCombate->setArmadura(Ventana::getInstancia()->getArmadura()*5);

    statsnull = Sprite(CargaSprites::getTexture("resources/HabilidadesNEW.png"));
    statsnull.setTextureRect(sf::IntRect(0, 600, 730, 200));
    statsnull.setPosition(110, 870);
    statsenemy = Sprite(CargaSprites::getTexture("resources/HabilidadesNEW.png"));
    statsenemy.setTextureRect(sf::IntRect(0, 600, 730, 200));
    statsenemy.setPosition(1100, 870);
    //enemigos[2] = NULL;

    // CREAR ANIMACIONES
    //animaNull = new AnimaSprites("resources/spritesheet2.png", 10, 3, 2, 8, 0.15f);
    //nullSprite = &animaNull -> getSprite();

    // CARGAR HABILIDADES
    resetHabilidades();

    // CARGAR HITBOXES
    for(int i=0, j=1200; i<3; i++, j+=250) {

        posiciones[i] = sf::Sprite(CargaSprites::getTexture("resources/mirilla.png"));
        posiciones[i].setScale(0.45f, 0.45f);
        posiciones[i].setPosition(j, 490);
        posiciones[i].setOrigin(posiciones[i].getTexture()->getSize().x/2, posiciones[i].getTexture()->getSize().y/2);
    }

    fade = sf::Sprite(CargaSprites::getTexture("resources/Fade.png"));
    fade.setColor(Color(255, 255, 255, opacidadFade));
    fondob = Sprite(CargaSprites::getTexture("resources/panelcomb.png"));
    fondom = Sprite(CargaSprites::getTexture("resources/panelcomb2.png"));
    quem1 = Sprite(CargaSprites::getTexture("resources/quemadura.png"));
    quem2 = Sprite(CargaSprites::getTexture("resources/quemadura.png"));
    quem3 = Sprite(CargaSprites::getTexture("resources/quemadura.png"));
    hack1 = Sprite(CargaSprites::getTexture("resources/hackeado.png"));
    hack2 = Sprite(CargaSprites::getTexture("resources/hackeado.png"));
    hack3 = Sprite(CargaSprites::getTexture("resources/hackeado.png"));

    fondob.setScale(1.16,1.16);
    fondom.setScale(1.16,1.16);

    quem1.setPosition(950,200);
    quem1.setScale(0.3,0.3);
    quem2.setPosition(1255,200);
    quem2.setScale(0.3,0.3);
    hack1.setPosition(1010,200);
    hack1.setScale(0.3,0.3);
    hack2.setPosition(1315,200);
    hack2.setScale(0.3,0.3);

    // NULL
    nullSprite.setPosition(360 * Ventana::getInstancia()->tamX / 1920, 300 * Ventana::getInstancia()->tamY / 1080);
    nullSprite.setScale(0.48, 0.48);

    resetearValores(true);
}

void Ecomb::cargarTextos() {

    indicadorVidaNull.setFont(fuente);
    indicadorVidaNull.setString(std::to_string(nullCombate->getVida()));
    indicadorVidaNull.setColor(Color(192, 0, 255));
    indicadorVidaNull.setPosition(255, 945);
    indicadorVidaNull.setCharacterSize(50);

    indicadorDanoNull.setFont(fuente);
    indicadorDanoNull.setString(std::to_string(nullCombate->getDano()));
    indicadorDanoNull.setColor(Color(192, 0, 255));
    indicadorDanoNull.setPosition(675, 945);
    indicadorDanoNull.setCharacterSize(50);

    indicadorArmaduraNull.setFont(fuente);
    indicadorArmaduraNull.setString(std::to_string(nullCombate->getArmadura()));
    indicadorArmaduraNull.setColor(Color(192, 0, 255));
    indicadorArmaduraNull.setPosition(365, 995);
    indicadorArmaduraNull.setCharacterSize(50);

    indicadorCriticoNull.setFont(fuente);
    indicadorCriticoNull.setString(std::to_string(nullCombate->getCritico()));
    indicadorCriticoNull.setColor(Color(192, 0, 255));
    indicadorCriticoNull.setPosition(695, 995);
    indicadorCriticoNull.setCharacterSize(50);

    numPocion.setFont(fuente);
    numPocion.setString(std::to_string(pociones));
    numPocion.setColor(Color(2, 184, 255));
    numPocion.setPosition(642, 820);
    numPocion.setCharacterSize(50);

    numCohete.setFont(fuente);
    numCohete.setString(std::to_string(ulti));
    numCohete.setColor(Color(2, 184, 255));
    numCohete.setPosition(785, 820);
    numCohete.setCharacterSize(50);
    /*
    for(int i=0; i<3; i++) {

        if(enemigos[i] != NULL) {

            vidas[i].setFont(fuente);
            vidas[i].setString(std::to_string(enemigos[i]->getVida()));
            vidas[i].setColor(Color(66, 3, 244));
            vidas[i].setPosition(enemigos[i]->getSprite().getPosition().x + 70, enemigos[i]->getSprite().getPosition().y - 80);
            vidas[i].setCharacterSize(70);
        }
    }
    */
}

void Ecomb::cargarTextos(int i) {

    dibujaenemi = i;
    vidas[i].setFont(fuente);
    vidas[i].setString(std::to_string(enemigos[i]->getVida()));
    vidas[i].setColor(Color(192, 0, 255));
    vidas[i].setPosition(1255, 945);
    vidas[i].setCharacterSize(50);

    dano[i].setFont(fuente);
    dano[i].setString(std::to_string(enemigos[i]->getDano()));
    dano[i].setColor(Color(192, 0, 255));
    dano[i].setPosition(1675, 945);
    dano[i].setCharacterSize(50);

    armadura[i].setFont(fuente);
    armadura[i].setString(std::to_string(enemigos[i]->getArmadura()));
    armadura[i].setColor(Color(192, 0, 255));
    armadura[i].setPosition(1365, 995);
    armadura[i].setCharacterSize(50);

    critico[i].setFont(fuente);
    critico[i].setString(std::to_string(enemigos[i]->getCritico()));
    critico[i].setColor(Color(192, 0, 255));
    critico[i].setPosition(1695, 995);
    critico[i].setCharacterSize(50);
}

void Ecomb::correrEventos() {

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)) {
        repintaHabilidades(0);
        Ventana::getInstancia()->sonido->PlaySound(6);
        habilidadElegida = 1;
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)) {
        repintaHabilidades(1);
        Ventana::getInstancia()->sonido->PlaySound(6);
        habilidadElegida = 2;
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num3)) {
        repintaHabilidades(2);
        Ventana::getInstancia()->sonido->PlaySound(6);
        habilidadElegida = 3;
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num4)) {
        repintaHabilidades(3);
        Ventana::getInstancia()->sonido->PlaySound(6);
        habilidadElegida = 4;
        enemigoElegido = -1;
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num5)) {
        repintaHabilidades(4);
        Ventana::getInstancia()->sonido->PlaySound(6);
        habilidadElegida = 5;
        enemigoElegido = -1;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {

        if(seleccionando==false && habilidadElegida!=4 && habilidadElegida!=5) {

            if(enemigoElegido==2) {

                if(enemigos[1]!=NULL) {

                    enemigoElegido=1;
                    Ventana::getInstancia()->sonido->PlaySound(14);
                    cargarTextos(1);
                }
                else if(enemigos[0]!=NULL) {

                    enemigoElegido=0;
                    Ventana::getInstancia()->sonido->PlaySound(14);
                    cargarTextos(0);
                }
            }
            else if(enemigoElegido==1) {

                if(enemigos[0]!=NULL) {

                    enemigoElegido=0;
                    Ventana::getInstancia()->sonido->PlaySound(14);
                    cargarTextos(0);
                }
                else if(enemigos[2]!=NULL) {

                    enemigoElegido=2;
                    Ventana::getInstancia()->sonido->PlaySound(14);
                    cargarTextos(2);
                }
            }
            else if(enemigoElegido==0) {

                if(enemigos[2]!=NULL) {

                    enemigoElegido=2;
                    Ventana::getInstancia()->sonido->PlaySound(14);
                    cargarTextos(2);
                }
                else if(enemigos[1]!=NULL) {

                    enemigoElegido=1;
                    Ventana::getInstancia()->sonido->PlaySound(14);
                    cargarTextos(1);
                }
            }
            else {

                if(enemigos[2]!=NULL) {

                    enemigoElegido=2;
                    Ventana::getInstancia()->sonido->PlaySound(14);
                    cargarTextos(2);
                }
                else if(enemigos[1]!=NULL) {

                    enemigoElegido=1;
                    Ventana::getInstancia()->sonido->PlaySound(14);
                    cargarTextos(1);
                }
                else if(enemigos[0]!=NULL) {

                    enemigoElegido=0;
                    Ventana::getInstancia()->sonido->PlaySound(14);
                    cargarTextos(0);
                }
            }
        }

        seleccionando = true;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {

        if(seleccionando==false && habilidadElegida!=4 && habilidadElegida!=5) {

            if(enemigoElegido==2) {

                if(enemigos[0]!=NULL) {

                    enemigoElegido=0;
                    Ventana::getInstancia()->sonido->PlaySound(14);
                    cargarTextos(0);
                }
                else if(enemigos[1]!=NULL) {

                    enemigoElegido=1;
                    Ventana::getInstancia()->sonido->PlaySound(14);
                    cargarTextos(1);
                }
            }
            else if(enemigoElegido==0) {

                if(enemigos[1]!=NULL) {

                    enemigoElegido=1;
                    Ventana::getInstancia()->sonido->PlaySound(14);
                    cargarTextos(1);
                }
                else if(enemigos[2]!=NULL) {

                    enemigoElegido=2;
                    Ventana::getInstancia()->sonido->PlaySound(14);
                    cargarTextos(2);
                }
            }
            else if(enemigoElegido==1) {

                if(enemigos[2]!=NULL) {

                    enemigoElegido=2;
                    Ventana::getInstancia()->sonido->PlaySound(14);
                    cargarTextos(2);
                }
                else if(enemigos[0]!=NULL) {

                    enemigoElegido=0;
                    Ventana::getInstancia()->sonido->PlaySound(14);
                    cargarTextos(0);
                }
            }
            else {

                if(enemigos[0]!=NULL) {

                    enemigoElegido=0;
                    Ventana::getInstancia()->sonido->PlaySound(14);
                    cargarTextos(0);
                }
                else if(enemigos[1]!=NULL) {

                    enemigoElegido=1;
                    Ventana::getInstancia()->sonido->PlaySound(14);
                    cargarTextos(1);
                }
                else if(enemigos[2]!=NULL) {

                    enemigoElegido=2;
                    Ventana::getInstancia()->sonido->PlaySound(14);
                    cargarTextos(2);
                }
            }
        }

        seleccionando = true;
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::F)) {

        if(plant==4) {

            Ventana::getInstancia() -> world.setState(4);
        }
        else {

            Ventana::getInstancia() -> world.setState(2);
            eplat.sonarSonidos();
        }

    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::G)) {

        modoDios = true;
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {

        if (turno == true && habilidadElegida >= 0 && (enemigoElegido >= 0 || habilidadElegida == 4 || habilidadElegida == 5)) {    // MI TURNO

            Clock relojSpriteAtaque;

            if(habilidadElegida == 1){

                int golpe = nullCombate->habilidadNull1();

                bool efecto = false;

                if(golpe < 0);
                    efecto = true;

                golpe = abs(golpe);

                //Sprite spriteAtaque = nullCombate->getSpriteAtaque();
                Sprite spriteAtaque = Sprite(CargaSprites::getTexture("resources/nullataque.png"));
                spriteAtaque.setScale(0.611,0.611);
                spriteAtaque.setPosition(-10, 200);
                Sprite spriteImpacto = enemigos[enemigoElegido]->getSpriteImpacto();

                Ventana::getInstancia()->sonido->PlaySound(8);

                while (relojSpriteAtaque.getElapsedTime().asSeconds() < 4.5f) {

                    lanzarAtaque(spriteAtaque, spriteImpacto, true);
                }

                golpe = golpe - enemigos[enemigoElegido]->getArmadura()/10;
                enemigos[enemigoElegido]->setVida(golpe);
                resetearValores(false);
                habilidadElegida = -1;
                enemigoElegido = -1;
                relojAtaque.restart();
                resetHabilidades();
                dibujaenemi = -1;
            }

            if(habilidadElegida == 2){

                int golpe = nullCombate->habilidadNull2();
                bool efecto = false;

                if(golpe < 0);
                    efecto = true;

                golpe = abs(golpe);

                //Sprite spriteAtaque = nullCombate->getSpriteAtaque();
                Sprite spriteAtaque = Sprite(CargaSprites::getTexture("resources/nullpistola.png"));
                spriteAtaque.setScale(0.55,0.55);
                spriteAtaque.setPosition(-10, 200);
                Sprite spriteImpacto = enemigos[enemigoElegido]->getSpriteImpacto();

                Ventana::getInstancia()->sonido->PlaySound(9);
                while (relojSpriteAtaque.getElapsedTime().asSeconds() < 4.5f) {

                    lanzarAtaque(spriteAtaque, spriteImpacto, true);
                }

                golpe = golpe - enemigos[enemigoElegido]->getArmadura()/10;
                enemigos[enemigoElegido]->setVida(golpe);

                if(efecto){

                    enemigos[enemigoElegido]->quemado();
                }

                resetearValores(false);
                habilidadElegida = -1;
                enemigoElegido = -1;
                relojAtaque.restart();
                resetHabilidades();
                dibujaenemi = -1;
            }

            if(habilidadElegida == 3){

                int golpe = nullCombate->habilidadNull3();
                bool efecto = false;

                if(golpe < 0);
                    efecto = true;

                golpe = abs(golpe);

                //Sprite spriteAtaque = nullCombate->getSpriteAtaque();
                Sprite spriteAtaque = Sprite(CargaSprites::getTexture("resources/nullhack.png"));
                spriteAtaque.setScale(0.611,0.611);
                spriteAtaque.setPosition(-10, 200);
                Sprite spriteImpacto = enemigos[enemigoElegido]->getSpriteImpacto();

                Ventana::getInstancia()->sonido->PlaySound(11);
                while (relojSpriteAtaque.getElapsedTime().asSeconds() < 4.5f) {

                    lanzarAtaque(spriteAtaque, spriteImpacto, true);
                }

                golpe = golpe - enemigos[enemigoElegido]->getArmadura()/10;
                enemigos[enemigoElegido]->setVida(golpe);

                if(efecto){

                    if(hackeo == -1){

                        enemigos[enemigoElegido]->hackeado();
                    }

                    if(golpe == 0){

                        hackeo = -1;
                    }
                }

                resetearValores(false);
                habilidadElegida = -1;
                enemigoElegido = -1;
                relojAtaque.restart();
                resetHabilidades();
                dibujaenemi = -1;
            }

            if(habilidadElegida == 4){

                if(pociones > 0){

                    int golpe = nullCombate->habilidadNull4(pociones);

                    //Sprite spriteAtaque = nullCombate->getSpriteAtaque();
                    Sprite spriteAtaque = Sprite(CargaSprites::getTexture("resources/nullcombcura.png"));
                    spriteAtaque.setScale(0.611,0.611);
                    spriteAtaque.setPosition(-10, 200);
                    Sprite spriteImpacto = spriteVacio;

                    Ventana::getInstancia()->sonido->PlaySound(10);
                    while (relojSpriteAtaque.getElapsedTime().asSeconds() < 4.5f) {

                        lanzarAtaque(spriteAtaque, spriteImpacto, true);
                    }

                    nullCombate->setVida(golpe*-1);
                    resetearValores(false);
                    habilidadElegida = -1;
                    enemigoElegido = -1;
                    relojAtaque.restart();
                    resetHabilidades();
                    dibujaenemi = -1;
                    pociones--;
                }
            }

            if(habilidadElegida == 5){

                if(ulti == 1){

                    int golpe = nullCombate->habilidadNull5();

                    //Sprite spriteAtaque = nullCombate->getSpriteAtaque();
                    Sprite spriteAtaque = Sprite(CargaSprites::getTexture("resources/nullulti.png"));
                    spriteAtaque.setScale(0.611,0.611);
                    spriteAtaque.setPosition(-10, 200);
                    Sprite spriteImpacto;

                    if(enemigos[0] != NULL){
                        spriteImpacto = enemigos[0]->getSpriteAtaque();
                    }
                    else if(enemigos[1] != NULL){
                        spriteImpacto = enemigos[1]->getSpriteAtaque();
                    }
                    else if(enemigos[2] != NULL){
                        spriteImpacto = enemigos[2]->getSpriteAtaque();
                    }

                    Ventana::getInstancia()->sonido->PlaySound(12);
                    while (relojSpriteAtaque.getElapsedTime().asSeconds() < 4.5f) {

                        lanzarAtaque(spriteAtaque, spriteImpacto, true);
                    }

                    for(int i = 0 ; i < 3 ; i++){

                        if(enemigos[i] != NULL){

                            golpe = golpe - enemigos[enemigoElegido]->getArmadura()/10;
                            enemigos[i]->setVida(golpe);
                        }
                    }
                    resetearValores(false);
                    habilidadElegida = -1;
                    enemigoElegido = -1;
                    relojAtaque.restart();
                    resetHabilidades();
                    dibujaenemi = -1;
                    ulti--;
                }
            }
        }
    }

    if (Mouse::isButtonPressed(Mouse::Left)) {

        // SI CLICAS EN UNA HABILIDAD
        for(int i=0; i<5; i++) {

            if(posicionRaton.x >= habilidades[i].getPosition().x && posicionRaton.x <= habilidades[i].getPosition().x+(habilidades[i].getTexture()->getSize().x*habilidades[i].getScale().x) && posicionRaton.y >= habilidades[i].getPosition().y && posicionRaton.y <= habilidades[i].getPosition().y+(habilidades[i].getTexture()->getSize().x*habilidades[i].getScale().y)) {
                repintaHabilidades(i);
                habilidadElegida = i + 1;
                Ventana::getInstancia()->sonido->PlaySound(6);
                if(habilidadElegida==4 || habilidadElegida==5) {

                    enemigoElegido = -1;
                }
            }
        }

        // SI CLICAS EN UN SPRITE ENEMIGO
        for(int i=0; i<3; i++) {

            if(enemigos[i] != NULL) {

                if(posicionRaton.x >= enemigos[i]->getSprite().getPosition().x && posicionRaton.x <= enemigos[i]->getSprite().getPosition().x + enemigos[i]->getTextura().getSize().x && posicionRaton.y >= enemigos[i]->getSprite().getPosition().y && posicionRaton.y <= enemigos[i]->getSprite().getPosition().y + enemigos[i]->getTextura().getSize().y) {

                    if(habilidadElegida!=4 && habilidadElegida!=5) {

                        enemigoElegido = i;
                        Ventana::getInstancia()->sonido->PlaySound(14);
                        cargarTextos(i);
                    }
                    else {

                        enemigoElegido = -1;
                    }
                }
            }
        }
    }
    else if(!sf::Keyboard::isKeyPressed(sf::Keyboard::Right)&&!sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){

        seleccionando = false;
    }
}

void Ecomb::correrRaton() {

    posicionRaton = Mouse::getPosition(Ventana::getInstancia() -> window);
    posicionRaton = (Vector2i)Ventana::getInstancia() -> window.mapPixelToCoords(posicionRaton);
}

void Ecomb::bucleJuego() {

    // std::cout << "" << std::endl;

    //while (Ventana::getInstancia() -> window.isOpen() && Ventana::getInstancia() -> world.getState()==3) {

    combatir();
    correrEventos();
    correrRaton();
    //}
}

Ecomb::~Ecomb() {

    delete nullCombate;
    delete animaNull;
    delete atacante;
    delete enemigos[1];
    delete enemigos[2];
    delete enemigos[3];
}

void Ecomb::resetHabilidades() {

    for(int i=0, j=147; i<5; i++, j+=145) {
        if(i == 0) {
            habilidades[i] = sf::Sprite(CargaSprites::getTexture("resources/Espadazo.png"));
        }
        else if(i == 1) {
            habilidades[i] = sf::Sprite(CargaSprites::getTexture("resources/Pistola.png"));
        }
        else if(i == 2) {
            habilidades[i] = sf::Sprite(CargaSprites::getTexture("resources/Hackeo.png"));
        }
        else if(i == 3) {
            habilidades[i] = sf::Sprite(CargaSprites::getTexture("resources/jeringa.png"));
        }
        else if(i == 4) {
            habilidades[i] = sf::Sprite(CargaSprites::getTexture("resources/Espada.png"));
        }
        habilidades[i].setPosition(j, 784);
        habilidades[i].setScale(0.1764, 0.1764);

        textohabilidad = sf::Sprite(CargaSprites::getTexture("resources/Habilidades.png"));
        textohabilidad.setTextureRect(sf::IntRect(800, 600, 730, 200));
        //sprite.setScale(2.9, 2.9);
        textohabilidad.setPosition(1100, 685);
    }
}

void Ecomb::repintaHabilidades(int num) {

    if(num == 0){
        for(int i=0, j=147; i<5; i++, j+=145) {
            if(i == 0) {
                habilidades[i] = sf::Sprite(CargaSprites::getTexture("resources/Espadazo2a.png"));
            }
            else if(i == 1) {
                habilidades[i] = sf::Sprite(CargaSprites::getTexture("resources/Pistola.png"));
            }
            else if(i == 2) {
                habilidades[i] = sf::Sprite(CargaSprites::getTexture("resources/Hackeo.png"));
            }
            else if(i == 3) {
                habilidades[i] = sf::Sprite(CargaSprites::getTexture("resources/jeringa.png"));
            }
            else if(i == 4) {
                habilidades[i] = sf::Sprite(CargaSprites::getTexture("resources/Espada.png"));
            }
            habilidades[i].setPosition(j, 784);
            habilidades[i].setScale(0.1764, 0.1764);

            textohabilidad = sf::Sprite(CargaSprites::getTexture("resources/Habilidades.png"));
            textohabilidad.setTextureRect(sf::IntRect(0, 0, 500, 200));
            //sprite.setScale(2.9, 2.9);
            textohabilidad.setPosition(1150, 740);
        }
    }

    else if(num == 1){
        for(int i=0, j=147; i<5; i++, j+=145) {
            if(i == 0) {
                habilidades[i] = sf::Sprite(CargaSprites::getTexture("resources/Espadazo.png"));
            }
            else if(i == 1) {
                habilidades[i] = sf::Sprite(CargaSprites::getTexture("resources/Pistola2.png"));
            }
            else if(i == 2) {
                habilidades[i] = sf::Sprite(CargaSprites::getTexture("resources/Hackeo.png"));
            }
            else if(i == 3) {
                habilidades[i] = sf::Sprite(CargaSprites::getTexture("resources/jeringa.png"));
            }
            else if(i == 4) {
                habilidades[i] = sf::Sprite(CargaSprites::getTexture("resources/Espada.png"));
            }
            habilidades[i].setPosition(j, 784);
            habilidades[i].setScale(0.1764, 0.1764);

            textohabilidad = sf::Sprite(CargaSprites::getTexture("resources/Habilidades.png"));
            textohabilidad.setTextureRect(sf::IntRect(700, 0, 740, 200));
            //sprite.setScale(2.9, 2.9);
            textohabilidad.setPosition(1100, 720);
        }
    }

    else if(num == 2){
        for(int i=0, j=147; i<5; i++, j+=145) {
            if(i == 0) {
                habilidades[i] = sf::Sprite(CargaSprites::getTexture("resources/Espadazo.png"));
            }
            else if(i == 1) {
                habilidades[i] = sf::Sprite(CargaSprites::getTexture("resources/Pistola.png"));
            }
            else if(i == 2) {
                habilidades[i] = sf::Sprite(CargaSprites::getTexture("resources/Hackeo2.png"));
            }
            else if(i == 3) {
                habilidades[i] = sf::Sprite(CargaSprites::getTexture("resources/jeringa.png"));
            }
            else if(i == 4) {
                habilidades[i] = sf::Sprite(CargaSprites::getTexture("resources/Espada.png"));
            }
            habilidades[i].setPosition(j, 784);
            habilidades[i].setScale(0.1764, 0.1764);

            textohabilidad = sf::Sprite(CargaSprites::getTexture("resources/Habilidades.png"));
            textohabilidad.setTextureRect(sf::IntRect(0, 200, 730, 200));
            //sprite.setScale(2.9, 2.9);
            textohabilidad.setPosition(1100, 710);
        }
    }

    else if(num == 3){
        for(int i=0, j=147; i<5; i++, j+=145) {
            if(i == 0) {
                habilidades[i] = sf::Sprite(CargaSprites::getTexture("resources/Espadazo.png"));
            }
            else if(i == 1) {
                habilidades[i] = sf::Sprite(CargaSprites::getTexture("resources/Pistola.png"));
            }
            else if(i == 2) {
                habilidades[i] = sf::Sprite(CargaSprites::getTexture("resources/Hackeo.png"));
            }
            else if(i == 3) {
                habilidades[i] = sf::Sprite(CargaSprites::getTexture("resources/jeringa2.png"));
            }
            else if(i == 4) {
                habilidades[i] = sf::Sprite(CargaSprites::getTexture("resources/Espada.png"));
            }
            habilidades[i].setPosition(j, 784);
            habilidades[i].setScale(0.1764, 0.1764);

            textohabilidad = sf::Sprite(CargaSprites::getTexture("resources/Habilidades.png"));
            textohabilidad.setTextureRect(sf::IntRect(700, 200, 730, 200));
            //sprite.setScale(2.9, 2.9);
            textohabilidad.setPosition(1150, 730);
        }
    }

    else if(num == 4){
        for(int i=0, j=147; i<5; i++, j+=145) {
            if(i == 0) {
                habilidades[i] = sf::Sprite(CargaSprites::getTexture("resources/Espadazo.png"));
            }
            else if(i == 1) {
                habilidades[i] = sf::Sprite(CargaSprites::getTexture("resources/Pistola.png"));
            }
            else if(i == 2) {
                habilidades[i] = sf::Sprite(CargaSprites::getTexture("resources/Hackeo.png"));
            }
            else if(i == 3) {
                habilidades[i] = sf::Sprite(CargaSprites::getTexture("resources/jeringa.png"));
            }
            else if(i == 4) {
                habilidades[i] = sf::Sprite(CargaSprites::getTexture("resources/Espada2a.png"));
            }
            habilidades[i].setPosition(j, 784);
            habilidades[i].setScale(0.1764, 0.1764);

            textohabilidad = sf::Sprite(CargaSprites::getTexture("resources/Habilidades.png"));
            textohabilidad.setTextureRect(sf::IntRect(0, 400, 730, 200));
            //sprite.setScale(2.9, 2.9);
            textohabilidad.setPosition(1100, 685);
        }
    }

}
