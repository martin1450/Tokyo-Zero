#ifndef EPLAT_H
#define EPLAT_H
#include "JugadorP.h"
#include "Objeto.h"
#include "Fuente.h"
#include "Npc.h"
#include "LevelFactory.h"
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include "TextoP.h"
#include "Agujero.h"

#include "Puerta.h"
using namespace std;

class Eplat
{
    public:
        Eplat();
        void inicializar();
        void render();
        void CargarEscena();
        void Dibujar();
        void AtravesarAgujero();


        void colisionesCabeza();
        void gravedad();
        void ajustador();

        void sonarSonidos();

        void DetectarColisionFuente();
        void DetectarColisionObjetos();
        void DetectarColisionAgujero();
        void DetectarColisionPuerta();
        void DetectarColisionEnemigos();
        void colsalto();
        void cabeza();
        void reinicio();


        //void RetirarObjeto(Objeto c);

        JugadorP& getPlayer(){return jugador;};
        Npc& getNpc(){return enemigos;};

        bool getEntrandoEnVortice(){return entrandoEnVortice;};

        bool getProceso(){return proceso;};

        float speed = 300.0f;

        virtual ~Eplat();
    protected:
    private:
        JugadorP jugador;
        Fuente* fuente;
        Agujero* agujero;
        Npc enemigos;

        Puerta* puertaFinNivel;
        Puerta* puertaInicioNivel;
        vector<Objeto> objetos;

        TextoP * textoObjeto;
        TextoP * textoFuente;
        TextoP * textoEnemigos;
        TextoP * textoAgujeroPuertas;

        int dirantigua = 1;
        int num=0;
        //Objeto * objetos;
        bool colisionObjeto;
        bool colisionFuente;
        bool colisionAgujero;
        bool colisionPuerta;
        bool colisionEnemigo;

        bool intentandoAbrirPuerta;

        int vorticeDestino;
        bool entrandoEnVortice;

        LevelFactory niv;
        sf::String pathSonido;

        bool proceso=false;


};

#endif // EPLAT_H
