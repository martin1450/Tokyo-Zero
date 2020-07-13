#ifndef STATE_H
#define STATE_H
#include <SFML/Graphics.hpp>
#include "Eplat.h"
#include "Menu.h"
#include "Ecomb.h"

class State
{
    public:
        State();
        void setEstado(int x);
        int getEstado();
        void nuevaBatalla(int plantilla);
        void comprobador();
        void controlador();
        void render();
        Eplat eplat;
        virtual ~State();
    protected:
    private:
        int estado;
        Menu* menu;
        Ecomb* juego;

};

#endif // STATE_H
