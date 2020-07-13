#include "Texto.h"

Texto::Texto()
{



}

Texto::Texto(bool cursiva, Colorea col, std::string contenido, int posX, int posY, int tamanyo)
{

    color = col;
    tcursiva = cursiva;
    tcontenido = contenido;
    tposX = posX;
    tposY = posY;
    ttam = tamanyo;

    //std::cout << textoCreado.get << std::endl;

}

Texto::~Texto()
{
    //dtor
}

sf::Text Texto::getTexto()
{
    if(tcursiva == true)
    {
        fuenteCursiva.loadFromFile("resources/Fonts/VoyagerGrotesque(regular).ttf");
        textoCreado.setFont(fuenteCursiva);
    }

    else
    {
        fuenteNoCursiva.loadFromFile("resources/quantummalicedrop.ttf");
        textoCreado.setFont(fuenteNoCursiva);
    }

    textoCreado.setColor(color.getColor());
    textoCreado.setString(tcontenido);
    textoCreado.setPosition(tposX, tposY);
    textoCreado.setCharacterSize(ttam);
    return textoCreado;

}

void Texto::setColor(sf::Uint8 r, sf::Uint8 g, sf::Uint8 b)
{

    color.setColor(r, g, b);
    textoCreado.setColor(color.getColor());

}

void Texto::setContenido(std::string contenido)
{

    tcontenido = contenido;

}

void Texto::setPosicion(int posX, int posY)
{

    tposX = posX;
    tposY = posY;

}

Colorea Texto::getColor()
{
    return color;

}
