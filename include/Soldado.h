#ifndef SOLDADO_H
#define SOLDADO_H

#include "Personaje.h"

class Soldado : public Personaje
{
    public:
        Soldado();
        int actuar();
        virtual ~Soldado();
    protected:
    private:
};

#endif // SOLDADO_H
