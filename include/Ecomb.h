#ifndef ECOMB_H
#define ECOMB_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include "Eplat.h"
#include "Personaje.h"
#include "Soldado.h"
#include "Mutante.h"
#include "Zero.h"

using namespace sf;

class AnimaSprites;

class Ecomb
{
    public:
        Ecomb(int plantilla);
        void cargarGraficos(int plantilla);
        void cargarTextos();
        void cargarTextos(int i);
        void correrEventos();
        void correrRaton();
        void bucleJuego();
        void resetHabilidades();
        void repintaHabilidades(int num);
        void combatir();
        void lanzarAtaque(Sprite &spriteAtaque, Sprite &spriteImpacto, bool nullAtaca);
        void resetearValores(bool pasaTurno);
        void elegirAtacante();
        ~Ecomb();

    private:
        RenderWindow *ventana;
        int fps;
        int tamX;
        int tamY;

        bool seleccionando;
        bool direccion0=true;
        bool direccion1=true;
        bool direccion2=true;
        bool direccion3=true;

        Font fuenteCombate;
        Text indicadorVidaNull;

        Sprite hud;
        Sprite fondoCombate;
        Sprite habilidades[5];

        Clock relojSprite;
        Clock relojAtaque;
        Clock relojSpriteN;

        Event evento;
        Vector2i posicionRaton;

        Personaje* nullCombate;
        Personaje* enemigos[3];
        Sprite posiciones[3];
        Text vidas[3];
        Personaje* atacante;

        Font fuenteCursiva;
        Font fuente;
        Text indicadorVida;

        int habilidadElegida = -1;
        int enemigoElegido = -1;

        AnimaSprites *animaNull;
        Sprite nullSprite;

        Sprite spriteAtaque1Null;
        Sprite spriteImpactoNull;
        Sprite spriteAtaqueEnemigo;
        Sprite spriteImpactoEnemigo;
        Sprite fade;
        Sprite fondob;
        Sprite fondom;
        Sprite quem1;
        Sprite hack1;
        Sprite quem2;
        Sprite hack2;
        Sprite quem3;
        Sprite hack3;
        Sprite spriteVacio;
        Sprite textohabilidad;

        float velocidadAtaque;
        int opacidad;
        int opacidadFade;

        //Cosas para mostrar habilidades de null
        Sprite statsnull;
        Sprite statsenemy;
        int dibujaenemi = -1;
        Text indicadorDanoNull;
        Text indicadorArmaduraNull;
        Text indicadorCriticoNull;
        Text dano[3];
        Text armadura[3];
        Text critico[3];
        Text numPocion;
        Text numCohete;

        int hackeo;
        int numenem;

        Eplat eplat;

        int pociones = 1;
        int ulti = 1;
        bool modoDios = false;
        int plant = 1;
};

#endif // Ecomb_H
