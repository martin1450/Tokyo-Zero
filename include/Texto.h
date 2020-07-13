#ifndef TEXTO_H
#define TEXTO_H
#include "Colorea.h"

class Texto
{
    public:
        Texto();
        Texto(bool cursiva, Colorea col, std::string contenido, int posX, int posY, int tamanyo);
        virtual ~Texto();
        sf::Text getTexto();
        void setColor(sf::Uint8 r, sf::Uint8 g, sf::Uint8 b);
        void setContenido(std::string contenido);
        void setPosicion(int posX, int posY);
        Colorea getColor();
    protected:
    private:
        sf::Text textoCreado;
        bool tcursiva;
        std::string tcontenido;
        int tposX;
        int tposY;
        int ttam;
        Colorea color;
        sf::Font fuenteCursiva;
        sf::Font fuenteNoCursiva;
};

#endif // TEXTO_H
