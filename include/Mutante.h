#ifndef MUTANTE_H
#define MUTANTE_H

#include "Personaje.h"

class Mutante : public Personaje
{
    public:
        Mutante();
        int actuar();
        virtual ~Mutante();
    protected:
    private:
};

#endif // MUTANTE_H
