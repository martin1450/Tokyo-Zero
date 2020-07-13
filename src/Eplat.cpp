#include "Eplat.h"
#include "JugadorP.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "World.h"
#include "Ventana.h"
#include "Objeto.h"
#include "TextoP.h"
#include "Npc.h"
#include "Puerta.h"
using namespace std;
Eplat::Eplat()
{
    //ctor
}

void Eplat::inicializar()
{
    Ventana::getInstancia()->factory.inicializar();

    textoObjeto = new TextoP(1);
    textoFuente = new TextoP(1);
    textoEnemigos = new TextoP(1);
    textoAgujeroPuertas = new TextoP(1);
    agujero = new Agujero();
    fuente = new Fuente();
    puertaFinNivel = new Puerta();
    puertaInicioNivel = new Puerta();

    sonarSonidos();
    enemigos.setLuchado(false);
    CargarEscena();
}

void Eplat::ajustador()
{
   float deltaTime = Ventana::getInstancia()->delta;
   sf::FloatRect shapeBoy = jugador.getBoy().getGlobalBounds();
   bool bucle = true;
   int i=0;
   while(bucle){
       int jugadorX = jugador.getBoy().getPosition().x;
       int jugadorY = jugador.getBoy().getPosition().y + shapeBoy.height/2-i;
       int tileX = floor(jugadorX/32);
       int tileY = floor(jugadorY/32);
       int tile = ((tileY-1)*120+tileX)-1;
        //std::cout << Ventana::getInstancia()->colisones[tile] << std::endl;
       if(Ventana::getInstancia()->colisones[tile] == 11598){
             i++;
             num = i;
       }else{
             jugador.getBoy().setPosition(jugador.getBoy().getPosition().x, jugador.getBoy().getPosition().y - (i-1));
             Ventana::getInstancia()->firstpos.y = jugador.getBoy().getPosition().y;
             bucle = false;
       }
   }
}
void Eplat::gravedad(){
   float deltaTime = Ventana::getInstancia()->delta;
   sf::FloatRect shapeBoy = jugador.getBoy().getGlobalBounds();
   int jugadorX = jugador.getBoy().getPosition().x;
   int jugadorY = jugador.getBoy().getPosition().y + shapeBoy.height/2;
   int tileX = floor(jugadorX/32);
   int tileY = floor(jugadorY/32);
   int tile = ((tileY-1)*120+tileX)-1;
    //std::cout << Ventana::getInstancia()->colisones[tile] << std::endl;
   if(Ventana::getInstancia()->colisones[tile] != 11598){
         Ventana::getInstancia()->caida = true;
         jugador.getBoy().setPosition(jugador.getBoy().getPosition().x, jugador.getBoy().getPosition().y + speed*deltaTime);
         Ventana::getInstancia()->firstpos.y = jugador.getBoy().getPosition().y;

         speed += (150.0f * Ventana::getInstancia()->updates)/60;
         std::cout << speed << std::endl;
         std::cout << "eo" << std::endl;

   }else{
         jugador.setIsJumping(false);
         Ventana::getInstancia()->caida = false;
         ajustador();
         speed = 300.0f;
   }
}

void Eplat::colisionesCabeza(){
    if(!Ventana::getInstancia()->agachado){
       int jugadorX = 0;
       sf::FloatRect shapeBoy = jugador.getBoy().getGlobalBounds();
       if(Ventana::getInstancia()->direccion == -1){
           jugadorX = jugador.getBoy().getPosition().x - shapeBoy.width/4;
       }else{
           jugadorX = jugador.getBoy().getPosition().x + shapeBoy.width/2;
       }
       int jugadorY = jugador.getBoy().getPosition().y - shapeBoy.width/2;
        int tileX = floor(jugadorX/32);
        int tileY = floor(jugadorY/32);
        int tile = ((tileY-1)*120+tileX)-1;

       if(Ventana::getInstancia()->colisones[tile] == 11598){
            jugador.getBoy().setPosition(Ventana::getInstancia()->lastpos.x , Ventana::getInstancia()->lastpos.y);
            Ventana::getInstancia()->firstpos = Ventana::getInstancia()->lastpos;
       }
    }
}

void Eplat::cabeza(){
   int jugadorX = 0;
       sf::FloatRect shapeBoy = jugador.getBoy().getGlobalBounds();
       if(Ventana::getInstancia()->direccion == -1){
           jugadorX = jugador.getBoy().getPosition().x;
       }else{
           jugadorX = jugador.getBoy().getPosition().x;
       }
       int jugadorY = jugador.getBoy().getPosition().y - shapeBoy.width/2;
        int tileX = floor(jugadorX/32);
        int tileY = floor(jugadorY/32);
        int tile = ((tileY-1)*120+tileX)-1;


   if(Ventana::getInstancia()->colisones[tile] == 11598){
        jugador.setCayendo(true);
        jugador.setSubiendo(false);
   }
}

void Eplat::render()
{

    jugador.getBoy().setPosition(Ventana::getInstancia()->lastpos*(1-Ventana::getInstancia()->percent) + Ventana::getInstancia()->firstpos*Ventana::getInstancia()->percent);
    if(Ventana::getInstancia()->factory.getNivel() == 2 || Ventana::getInstancia()->factory.getNivel() == 3){
        enemigos.getEnemigos().setPosition(Ventana::getInstancia()->lastposnpc*(1-Ventana::getInstancia()->percent) + Ventana::getInstancia()->firstposnpc*Ventana::getInstancia()->percent);
    }

    if(enemigos.getEnemigos().getPosition().x > enemigos.getPosicionInicial().x+110){
        enemigos.setCambio(true);
    }else if (enemigos.getEnemigos().getPosition().x < enemigos.getPosicionInicial().x-110){
        enemigos.setCambio(false);
    }

    Ventana::getInstancia()->cameraPosition.x = jugador.getBoy().getPosition().x-(1920/2);
    if( Ventana::getInstancia()->cameraPosition.x<0)
         Ventana::getInstancia()->cameraPosition.x = 0;
    if( Ventana::getInstancia()->cameraPosition.x>=1920)
         Ventana::getInstancia()->cameraPosition.x = 1920;

    Ventana::getInstancia()->camera.reset(sf::FloatRect( Ventana::getInstancia()->cameraPosition.x,  Ventana::getInstancia()->cameraPosition.y, 1920, 1056));


    if(jugador.getBoy().getPosition().x > 3840 && Ventana::getInstancia()->direccion == 1){
        jugador.getBoy().setPosition(Ventana::getInstancia()->lastpos);
        Ventana::getInstancia()->firstpos = Ventana::getInstancia()->lastpos;
    }
    if(jugador.getBoy().getPosition().x < 50 && Ventana::getInstancia()->direccion == -1){
        jugador.getBoy().setPosition(Ventana::getInstancia()->lastpos);
        Ventana::getInstancia()->firstpos = Ventana::getInstancia()->lastpos;
    }
    if(jugador.getBoy().getPosition().y > 1056){
        jugador.getBoy().setPosition(Ventana::getInstancia()->getLastControlPoint());
        Ventana::getInstancia()->firstpos = jugador.getBoy().getPosition();
        Ventana::getInstancia()->lastpos = jugador.getBoy().getPosition();
    }

    Ventana::getInstancia()->window.setView( Ventana::getInstancia()->camera);
    Ventana::getInstancia()->window.draw(Ventana::getInstancia()->fondo);
    Ventana::getInstancia()->factory.pintarse();

    for(int i = 0; i < objetos.size();i++){
        objetos[i].Levitar();
    }

    agujero->Rotar();
    if(entrandoEnVortice){
        AtravesarAgujero();
    }
    Dibujar();
}

void Eplat::CargarEscena(){
    objetos.clear();
    Ventana::getInstancia()->setkeyCard(false);

    if(Ventana::getInstancia()->factory.getNivel() == 1){
            jugador.cargar(sf::Vector2f(150, 615));
            puertaFinNivel->Cargar(sf::Vector2f(3675, 490), true, sf::String("resources/puertaCerrada.png"), true);
            fuente->Cargar(sf::Vector2f(800, 615));
            Objeto o1;
            objetos.push_back(o1);
            objetos[0].Cargar(sf::Vector2f(2900, 640), 3);
        }else if(Ventana::getInstancia()->factory.getNivel() == 2){
            jugador.cargar(sf::Vector2f(150, 525));
            fuente->Cargar(sf::Vector2f(550, 535));
            puertaFinNivel->Cargar(sf::Vector2f(3675, 390), true, sf::String("resources/puertaCerrada.png"), true);
            puertaInicioNivel->Cargar(sf::Vector2f(175, 420), false, sf::String("resources/puertaCerrada.png"), false);
            agujero->Cargar(sf::Vector2f(2400, 740), sf::Vector2f(3150, 360));
            //1 pocion, 2 armadura, 3 llave, 4 habilidad
            Objeto o1, o2;
            objetos.push_back(o1);
            objetos.push_back(o2);
            objetos[0].Cargar(sf::Vector2f(1470, 890), 1);
            objetos[1].Cargar(sf::Vector2f(2450, 300), 3);
            enemigos.cargar(sf::Vector2f(2140, 250), 1);
            enemigos.setPosicionInicial(sf::Vector2f(2140, 250));
        }else if(Ventana::getInstancia()->factory.getNivel() == 3){
            jugador.cargar(sf::Vector2f(150, 745));
            fuente->Cargar(sf::Vector2f(1800, 750));
            puertaFinNivel->Cargar(sf::Vector2f(1870, 195), true, sf::String("resources/puertaCerrada.png"), true);
            puertaInicioNivel->Cargar(sf::Vector2f(175, 635), false, sf::String("resources/puertaCerrada.png"), false);
            Objeto o1, o2;
            objetos.push_back(o1);
            objetos.push_back(o2);
            objetos[0].Cargar(sf::Vector2f(900, 770), 2);
            objetos[1].Cargar(sf::Vector2f(3730, 600), 3);
            enemigos.cargar(sf::Vector2f(2400, 380), 1);
            enemigos.setPosicionInicial(sf::Vector2f(2400, 380));
        }else if(Ventana::getInstancia()->factory.getNivel() == 4){
            jugador.cargar(sf::Vector2f(150, 650));
            fuente->Cargar(sf::Vector2f(800, 665));
            puertaFinNivel->Cargar(sf::Vector2f(3625, 675), true, sf::String("resources/puertaCerrada.png"), true);
            puertaInicioNivel->Cargar(sf::Vector2f(175, 545), false, sf::String("resources/puertaCerrada.png"), false);
            Objeto o1, o2, o3, o4, o5;
            objetos.push_back(o1);
            objetos.push_back(o2);
            objetos.push_back(o3);
            objetos[0].Cargar(sf::Vector2f(1780, 530), 1);
            objetos[1].Cargar(sf::Vector2f(2580, 870), 2);
            objetos[2].Cargar(sf::Vector2f(2290, 400), 3);
        }else if(Ventana::getInstancia()->factory.getNivel() == 5){
            jugador.cargar(sf::Vector2f(150, 455));
            fuente->Cargar(sf::Vector2f(700, 400));
            puertaFinNivel->Cargar(sf::Vector2f(3625, 602), true, sf::String("resources/puertaCerrada.png"), true);
            puertaInicioNivel->Cargar(sf::Vector2f(15, 350), false, sf::String("resources/puertaCerrada.png"), false);
            agujero->Cargar(sf::Vector2f(1200, 950), sf::Vector2f(2000, 320));
            Objeto o1, o2, o3, o4;
            objetos.push_back(o1);
            objetos.push_back(o2);
            objetos.push_back(o3);
            objetos.push_back(o4);
            objetos[0].Cargar(sf::Vector2f(1400, 500), 1);
            objetos[1].Cargar(sf::Vector2f(1600, 950), 4);
            objetos[2].Cargar(sf::Vector2f(500, 960), 2);
            objetos[3].Cargar(sf::Vector2f(2750, 1056/2), 3);
        }

        /*enemigos.cargar(sf::Vector2f(520, 650), 1);
        enemigos.setPosicionInicial(sf::Vector2f(520, 650));*/
    /*
        fuente->Cargar(sf::Vector2f(520, 635));
        agujero->Cargar(sf::Vector2f(1200, 620), sf::Vector2f(1900, 480));
        puertaFinNivel->Cargar(sf::Vector2f(3625, 502), true, sf::String("resources/puertaCerrada.png"), true);
        puertaInicioNivel->Cargar(sf::Vector2f(175, 515), false, sf::String("resources/puertaCerrada.png"), false);

        //OBJETOS
        Objeto o1, o2, o3, o4, o5;
        objetos.push_back(o1);
        objetos.push_back(o2);
        objetos.push_back(o3);
        objetos.push_back(o4);
        objetos.push_back(o5);
        objetos[0].Cargar(sf::Vector2f(800, 670), 1);
        objetos[1].Cargar(sf::Vector2f(2350, 1056/2), 1);
        objetos[2].Cargar(sf::Vector2f(2500, 1056/2), 2);
        objetos[3].Cargar(sf::Vector2f(2750, 1056/2), 3);
        objetos[4].Cargar(sf::Vector2f(3000, 1056/2), 4);*/
}

void Eplat::reinicio(){
    Ventana::getInstancia()->factory.setNivel(1);
    inicializar();
    Ventana::getInstancia()->camera.setCenter(1920/2,1056/2);
    Ventana::getInstancia()->window.setView( Ventana::getInstancia()->camera);
    Ventana::getInstancia()->world.setState(1);
    sonarSonidos();
}

void Eplat::Dibujar(){
    Ventana::getInstancia()->window.draw(fuente->getFontSprite());
    Ventana::getInstancia()->window.draw(agujero->getAgujero1Sprite());
    Ventana::getInstancia()->window.draw(agujero->getAgujero2Sprite());
    Ventana::getInstancia()->window.draw(puertaFinNivel->getPuertaSprite());
    Ventana::getInstancia()->window.draw(puertaInicioNivel->getPuertaSprite());
    for(int i = 0; i < objetos.size();i++){
        if(!objetos[i].GetCogido()){
            Ventana::getInstancia()->window.draw(objetos[i].getObjectSprite());
        }
    }
    if(Ventana::getInstancia()->factory.getNivel() == 2 || Ventana::getInstancia()->factory.getNivel() == 3){
        Ventana::getInstancia()->window.draw(enemigos.getEnemigos());
    }
    Ventana::getInstancia()->window.draw(jugador.getBoy());

    if(colisionObjeto){
        Ventana::getInstancia()->window.draw(textoObjeto->getTexto());
    }
    if(colisionFuente){
        Ventana::getInstancia()->window.draw(textoFuente->getTexto());
    }
    if(colisionAgujero || colisionPuerta){
        Ventana::getInstancia()->window.draw(textoAgujeroPuertas->getTexto());
    }
    if(colisionEnemigo){
        Ventana::getInstancia()->window.draw(textoEnemigos->getTexto());
    }

}

void Eplat::sonarSonidos(){
   cout << "ESTADO: " << Ventana::getInstancia()->world.getState() << endl;
    if(Ventana::getInstancia()->world.getState()==1){
                pathSonido="resources/menu.wav";
    }else if(Ventana::getInstancia()->world.getState()==2){
        if(Ventana::getInstancia()->factory.getNivel()==2){
                pathSonido="resources/cueva.wav";
        }else{
                pathSonido="resources/normal.wav";
        }
    }else{
        pathSonido="resources/combate.wav";
    }

    Ventana::getInstancia()->sonido->crear(pathSonido);
    Ventana::getInstancia()->sonido->sonar();
}

void Eplat::DetectarColisionObjetos(){
    int indice = -1;
    int tipo = 0;
    for(int i = 0; i < objetos.size(); i++){
        sf::FloatRect shapeBoy = jugador.getBoy().getGlobalBounds();
        sf::FloatRect shapeObjeto = objetos[i].getObjectSprite().getGlobalBounds();
        if(jugador.getBoy().getPosition().x+35 > objetos[i].getObjectSprite().getPosition().x-shapeObjeto.width/2 &&
            jugador.getBoy().getPosition().x-35 < objetos[i].getObjectSprite().getPosition().x+shapeObjeto.width/2 &&
            jugador.getBoy().getPosition().y+shapeBoy.height/2 > objetos[i].getObjectSprite().getPosition().y+shapeObjeto.height/2 &&
            jugador.getBoy().getPosition().y-shapeBoy.height/2 < objetos[i].getObjectSprite().getPosition().y-shapeObjeto.height/2 && !objetos[i].GetCogido()){
                tipo = objetos[i].getTipo();
                indice = i;
        }
    }
    if(tipo != 0 && indice != -1){
        colisionObjeto = true;
        if(tipo == 1){
            textoObjeto->Asignar(sf::Vector2f(objetos[indice].getObjectSprite().getPosition().x, objetos[indice].getObjectSprite().getPosition().y-300), "Pocion de vida(E)");
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::E)){
                objetos[indice].setCogido(true);
                Ventana::getInstancia()->setPociones(Ventana::getInstancia()->getPociones()+1);
                Ventana::getInstancia()->sonido->PlaySound(5);
            }
        }else if(tipo == 2){
            textoObjeto->Asignar(sf::Vector2f(objetos[indice].getObjectSprite().getPosition().x, objetos[indice].getObjectSprite().getPosition().y-300), "Armadura(E)");
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::E)){
                objetos[indice].setCogido(true);
                Ventana::getInstancia()->setArmadura(Ventana::getInstancia()->getArmadura()+1);
                Ventana::getInstancia()->sonido->PlaySound(5);
            }
        }else if(tipo == 3){
            textoObjeto->Asignar(sf::Vector2f(objetos[indice].getObjectSprite().getPosition().x, objetos[indice].getObjectSprite().getPosition().y-300), "Llave(E)");
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::E)){
                objetos[indice].setCogido(true);
                Ventana::getInstancia()->setkeyCard(true);
                Ventana::getInstancia()->sonido->PlaySound(1);
            }
        }else if(tipo == 4){
            textoObjeto->Asignar(sf::Vector2f(objetos[indice].getObjectSprite().getPosition().x, objetos[indice].getObjectSprite().getPosition().y-300), "Habilidad especial de combate (E)");
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::E)){
                objetos[indice].setCogido(true);
                Ventana::getInstancia()->setHabilidadExtra(true);
                Ventana::getInstancia()->sonido->PlaySound(5);
            }
        }
    }else{
        colisionObjeto = false;
    }
}

void Eplat::DetectarColisionFuente(){
    sf::FloatRect shapeBoy = jugador.getBoy().getGlobalBounds();
    sf::FloatRect shapeFuente = fuente->getFontSprite().getGlobalBounds();
    if(jugador.getBoy().getPosition().x+35 > fuente->getFontSprite().getPosition().x-shapeFuente.width/2 &&
            jugador.getBoy().getPosition().x-35 < fuente->getFontSprite().getPosition().x+shapeFuente.width/2 &&
            jugador.getBoy().getPosition().y+shapeBoy.height/2 > fuente->getFontSprite().getPosition().y+shapeFuente.height/2 &&
            jugador.getBoy().getPosition().y-shapeBoy.height/2 < fuente->getFontSprite().getPosition().y-shapeFuente.height/2){
            if(!fuente->GetUsada()){
                Ventana::getInstancia()->setLastControlPoint(fuente->getFontSprite().getPosition());
                fuente->Activar();
            }else{
                colisionFuente = true;
                if(Ventana::getInstancia()->factory.getNivel() == 1){
                    textoFuente->Asignar(sf::Vector2f(fuente->getFontSprite().getPosition().x, fuente->getFontSprite().getPosition().y+250), "Fuente activada, reapareceras aqui cuando mueras");
                }else{
                    textoFuente->Asignar(sf::Vector2f(fuente->getFontSprite().getPosition().x, fuente->getFontSprite().getPosition().y-250), "Fuente activada, reapareceras aqui cuando mueras");
                }

            }
    }else{
        colisionFuente = false;
    }
}

void Eplat::DetectarColisionAgujero(){
    sf::FloatRect shapeBoy = jugador.getBoy().getGlobalBounds();
    sf::FloatRect shapeAgujero1 = agujero->getAgujero1Sprite().getGlobalBounds();
    sf::FloatRect shapeAgujero2 = agujero->getAgujero2Sprite().getGlobalBounds();
    int numAgujero = 0;
    if(jugador.getBoy().getPosition().x > agujero->getAgujero1Sprite().getPosition().x-shapeAgujero1.width/2 &&
        jugador.getBoy().getPosition().x < agujero->getAgujero1Sprite().getPosition().x+shapeAgujero1.width/2 &&
        jugador.getBoy().getPosition().y > agujero->getAgujero1Sprite().getPosition().y-shapeAgujero1.height/2 &&
        jugador.getBoy().getPosition().y < agujero->getAgujero1Sprite().getPosition().y+shapeAgujero1.height/2){
        numAgujero = 1;
    }else if(jugador.getBoy().getPosition().x > agujero->getAgujero2Sprite().getPosition().x-shapeAgujero2.width/2 &&
        jugador.getBoy().getPosition().x < agujero->getAgujero2Sprite().getPosition().x+shapeAgujero2.width/2 &&
        jugador.getBoy().getPosition().y > agujero->getAgujero2Sprite().getPosition().y-shapeAgujero2.height/2 &&
        jugador.getBoy().getPosition().y < agujero->getAgujero2Sprite().getPosition().y+shapeAgujero2.height/2){
        numAgujero = 2;
    }

    if(numAgujero == 1){
        colisionAgujero = true;
        textoAgujeroPuertas->Asignar(sf::Vector2f(agujero->getAgujero1Sprite().getPosition().x, agujero->getAgujero1Sprite().getPosition().y-250), "Vortice espacio-temporal (F). Cuidado con las interferencias");
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::F)){
            Ventana::getInstancia()->sonido->PlaySound(0);
            vorticeDestino = 2;
            entrandoEnVortice = true;
        }
    }else if(numAgujero == 2){
        colisionAgujero = true;
        textoAgujeroPuertas->Asignar(sf::Vector2f(agujero->getAgujero2Sprite().getPosition().x, agujero->getAgujero2Sprite().getPosition().y-250), "Vortice espacio-temporal(F). Cuidado con las interferencias");
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::F)){
            Ventana::getInstancia()->sonido->PlaySound(0);
            vorticeDestino = 1;
            entrandoEnVortice = true;
        }
    }else{
        colisionAgujero = false;
    }
}

void Eplat::AtravesarAgujero(){
    if(jugador.EntrarEnVortice()){
        entrandoEnVortice = false;
        if(vorticeDestino == 1){
            Ventana::getInstancia()->firstpos = agujero->getAgujero1Sprite().getPosition();
        }else if(vorticeDestino == 2){
            Ventana::getInstancia()->firstpos = agujero->getAgujero2Sprite().getPosition();
        }
    }
}

void Eplat::DetectarColisionPuerta(){
    sf::FloatRect shapeBoy = jugador.getBoy().getGlobalBounds();
    sf::FloatRect shapePuertaFin = puertaFinNivel->getPuertaSprite().getGlobalBounds();
    sf::FloatRect shapePuertaIni = puertaInicioNivel->getPuertaSprite().getGlobalBounds();
    int puerta = 0;
    if(jugador.getBoy().getPosition().x > puertaInicioNivel->getPuertaSprite().getPosition().x-shapePuertaIni.width/2 &&
        jugador.getBoy().getPosition().x < puertaInicioNivel->getPuertaSprite().getPosition().x+shapePuertaIni.width/2 &&
        jugador.getBoy().getPosition().y > puertaInicioNivel->getPuertaSprite().getPosition().y-shapePuertaIni.height/2 &&
        jugador.getBoy().getPosition().y < puertaInicioNivel->getPuertaSprite().getPosition().y+shapePuertaIni.height/2){
        puerta = 1; //PUERTA DEL PRINCIPIO
    }else if(jugador.getBoy().getPosition().x > puertaFinNivel->getPuertaSprite().getPosition().x-shapePuertaFin.width/2 &&
        jugador.getBoy().getPosition().x < puertaFinNivel->getPuertaSprite().getPosition().x+shapePuertaFin.width/2 &&
        jugador.getBoy().getPosition().y > puertaFinNivel->getPuertaSprite().getPosition().y-shapePuertaFin.height/2 &&
        jugador.getBoy().getPosition().y < puertaFinNivel->getPuertaSprite().getPosition().y+shapePuertaFin.height/2){
        puerta = 2; //PUERTA DEL FINAL
    }

    if(puerta == 1){
        colisionPuerta = true;
        textoAgujeroPuertas->Asignar(sf::Vector2f(puertaInicioNivel->getPuertaSprite().getPosition().x, puertaInicioNivel->getPuertaSprite().getPosition().y-250), "Continua, no mires atras");
    }else if(puerta == 2){
        colisionPuerta = true;
        if(!puertaFinNivel->getBloqueada()){ // || !puertaFinNivel->getConKey() ||
            if(Ventana::getInstancia()->factory.getNivel() == 3){
                textoAgujeroPuertas->Asignar(sf::Vector2f(puertaFinNivel->getPuertaSprite().getPosition().x, puertaFinNivel->getPuertaSprite().getPosition().y-60), "Pulsa 'E' para entrar");
            }else{
                textoAgujeroPuertas->Asignar(sf::Vector2f(puertaFinNivel->getPuertaSprite().getPosition().x, puertaFinNivel->getPuertaSprite().getPosition().y-250), "Pulsa 'E' para entrar");
            }

            if(sf::Keyboard::isKeyPressed(sf::Keyboard::E)){
                Ventana::getInstancia()->sonido->PlaySound(15);
                if(Ventana::getInstancia()->factory.getNivel() == 5){
                    Ventana::getInstancia()->world.nuevoMundo(4);
                    Ventana::getInstancia()->world.setState(3);
                    sonarSonidos();
                    enemigos.setLuchado(true);
                    Ventana::getInstancia()->camera.setCenter(1920/2,1056/2);
                    Ventana::getInstancia()->window.setView( Ventana::getInstancia()->camera);
                }else{
                    Ventana::getInstancia()->factory.cambiarNivel();
                    Ventana::getInstancia()->lastpos.x = 0.0f;
                    Ventana::getInstancia()->lastpos.y = 0.0f;
                    this->inicializar();
                }
            }
        }else{
            if(!intentandoAbrirPuerta){
                if(Ventana::getInstancia()->factory.getNivel() == 3){
                    textoAgujeroPuertas->Asignar(sf::Vector2f(puertaFinNivel->getPuertaSprite().getPosition().x, puertaFinNivel->getPuertaSprite().getPosition().y-60), "Pulsa 'F' para abrir");
                }else{
                    textoAgujeroPuertas->Asignar(sf::Vector2f(puertaFinNivel->getPuertaSprite().getPosition().x, puertaFinNivel->getPuertaSprite().getPosition().y-250), "Pulsa 'F' para abrir");
                }
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::F)){
                if(!Ventana::getInstancia()->getkeyCard()){
                    if(Ventana::getInstancia()->factory.getNivel() == 3){
                        textoAgujeroPuertas->Asignar(sf::Vector2f(puertaFinNivel->getPuertaSprite().getPosition().x, puertaFinNivel->getPuertaSprite().getPosition().y-60), "Necesitas una llave");
                    }else{
                        textoAgujeroPuertas->Asignar(sf::Vector2f(puertaFinNivel->getPuertaSprite().getPosition().x, puertaFinNivel->getPuertaSprite().getPosition().y-250), "Necesitas una llave");
                    }

                    intentandoAbrirPuerta = true;
                }else{
                    puertaFinNivel->setBloqueada(false);
                    puertaFinNivel->Desbloquear();

                    Ventana::getInstancia()->sonido->PlaySound(2);
                }
            }
        }
    }else{
        colisionPuerta = false;
        intentandoAbrirPuerta = false;
    }
}

void Eplat ::DetectarColisionEnemigos(){

    sf::FloatRect shapeBoy = jugador.getBoy().getGlobalBounds();
    sf::FloatRect shapeEnemigo = enemigos.getEnemigos().getGlobalBounds();
    if(jugador.getBoy().getPosition().x > enemigos.getEnemigos().getPosition().x+50-shapeEnemigo.width/2 &&
        jugador.getBoy().getPosition().x < enemigos.getEnemigos().getPosition().x+50+shapeEnemigo.width/2 &&
        jugador.getBoy().getPosition().y > enemigos.getEnemigos().getPosition().y+50-shapeEnemigo.height/2 &&
        jugador.getBoy().getPosition().y < enemigos.getEnemigos().getPosition().y+50+shapeEnemigo.height/2){
            if(!enemigos.getLuchado()){
                cout << "luchado" << endl;
                textoEnemigos->Asignar(sf::Vector2f(enemigos.getEnemigos().getPosition().x, enemigos.getEnemigos().getPosition().y-150), "Preparado para el combate...");
                    Ventana::getInstancia()->sonido->PlaySound(13);
                    if(Ventana::getInstancia()->factory.getNivel() == 2){
                            Ventana::getInstancia()->world.nuevoMundo(3);
                            Ventana::getInstancia()->world.setState(3);
                            sonarSonidos();
                            enemigos.setLuchado(true);
                            Ventana::getInstancia()->camera.setCenter(1920/2,1056/2);
                            Ventana::getInstancia()->window.setView( Ventana::getInstancia()->camera);
                        }
                        if(Ventana::getInstancia()->factory.getNivel() == 3){
                            Ventana::getInstancia()->world.nuevoMundo(2);
                            Ventana::getInstancia()->world.setState(3);
                            sonarSonidos();
                            enemigos.setLuchado(true);
                            Ventana::getInstancia()->camera.setCenter(1920/2,1056/2);
                            Ventana::getInstancia()->window.setView( Ventana::getInstancia()->camera);
                    }
            }else{
                colisionEnemigo = true;
                textoEnemigos->Asignar(sf::Vector2f(enemigos.getEnemigos().getPosition().x, enemigos.getEnemigos().getPosition().y-150), "Ya has luchado contra mi, vete");
            }
    }else{
        colisionEnemigo = false;
    }
}

/*
void Eplat ::DetectarColisionEnemigos(){

    sf::FloatRect shapeBoy = jugador.getBoy().getGlobalBounds();
    sf::FloatRect shapeEnemigo = enemigos.getEnemigos().getGlobalBounds();
    if(jugador.getBoy().getPosition().x+35 > enemigos.getEnemigos().getPosition().x-shapeEnemigo.width/2 &&
            jugador.getBoy().getPosition().x-35 < enemigos.getEnemigos().getPosition().x+shapeEnemigo.width/2 &&
            jugador.getBoy().getPosition().y+shapeBoy.height/2 > enemigos.getEnemigos().getPosition().y+shapeEnemigo.height/2 &&
            jugador.getBoy().getPosition().y-shapeBoy.height/2 < enemigos.getEnemigos().getPosition().y-shapeEnemigo.height/2){
            if(!enemigos.getLuchado()){
                cout << "luchado" << endl;

                textoEnemigos->Asignar(sf::Vector2f(enemigos.getEnemigos().getPosition().x, enemigos.getEnemigos().getPosition().y-250), "Preparado para el combate");
                enemigos.setLuchado(true);

            }else{
                colisionEnemigo = true;
                cout << "YA HAS LUCHADO" << endl;
                textoEnemigos->Asignar(sf::Vector2f(enemigos.getEnemigos().getPosition().x, enemigos.getEnemigos().getPosition().y-250), "Ya has luchado contra mi, vete");
            }
    }else{
        colisionEnemigo = false;
    }

}*/




Eplat::~Eplat()
{
    //dtor
}

   /* World* p1 = World::Instance();
    World*p2 = p1->Instance();
    World& red = * World::Instance();*/
