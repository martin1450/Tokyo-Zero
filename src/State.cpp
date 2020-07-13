#include "State.h"
#include <iostream>
#include <string>
#include "Eplat.h"
#include "Menu.h"
#include "Ecomb.h"
#include "Ventana.h"

State::State()
{

}

void State::setEstado(int x){
    estado = x;
}

int State::getEstado(){
    return estado;
}

void State::nuevaBatalla(int plantilla) {

    juego = new Ecomb(plantilla);
}

void State::comprobador(){

    std::cout << "Aqui me hallo" << std::endl;

    eplat.inicializar();
    menu = new Menu();
    juego = new Ecomb(1);

}

void State::controlador(){
    switch (estado){
        case 1:
            menu->procesEvent();
            break;
        case 2:
            if(!Ventana::getInstancia()->pausa){
                eplat.getPlayer().jump();
                if(!eplat.getPlayer().getIsJumping() && !eplat.getEntrandoEnVortice()){
                    eplat.getPlayer().moverse();
                    eplat.colisionesCabeza();
                }

                if(eplat.getPlayer().getCayendo()){
                    eplat.gravedad();
                   // eplat.colisionesCabeza();
                }

                if(eplat.getPlayer().getSubiendo()){
                    eplat.cabeza();

                   // eplat.colisionesCabeza();
                }

                if(!eplat.getNpc().getLuchado()){
                eplat.getNpc().movimiento();
                }


                eplat.DetectarColisionFuente();
                eplat.DetectarColisionObjetos();
                eplat.DetectarColisionAgujero();
                eplat.DetectarColisionPuerta();
                eplat.DetectarColisionEnemigos();
            }
            break;
        case 3:
            //juego->bucleJuego();
            break;
        case 4:

            break;
    }
}


void State::render(){

    switch (estado){
        case 1:
            menu->dibujar();
            break;
        case 2:
            eplat.render();
            break;
        case 3:
            juego->bucleJuego();
            break;
        case 4:
            Ventana::getInstancia()->window.clear();
            Ventana::getInstancia()->window.draw(Ventana::getInstancia()->fin);
            Ventana::getInstancia()->window.display();
            break;
    }

}

State::~State()
{
    delete menu;
    delete juego;
}
