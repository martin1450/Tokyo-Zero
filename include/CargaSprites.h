#ifndef CARGASPRITES_H
#define CARGASPRITES_H

#include <SFML/Graphics.hpp>
#include <map>
#include <assert.h>

using namespace sf;

class CargaSprites {

    public:
        CargaSprites();
        static Texture& getTexture(std::string const& archivo);
    private:
        std::map <std::string, Texture> m_Texturas;

        // Esta rola es un Singleton, por lo que solo existe una instancia
        // de la misma, Instancia actua de puntero estatico al cargaSprites
        static CargaSprites* Instancia;
};

#endif // CARGASPRITES_H
