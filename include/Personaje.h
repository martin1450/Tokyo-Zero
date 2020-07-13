#ifndef PERSONAJE_H
#define PERSONAJE_H

using namespace sf;

class Personaje
{
    public:
        Personaje();
        int actuar();
        int habilidadNull1();
        int habilidadNull2();
        int habilidadNull3();
        int habilidadNull4(int pociones);
        int habilidadNull5();
        void quemado();
        int hackeado();
        void comprobarVida();
        void setArmadura(int armor);
        void setVida(int hit);
        int getVida();
        void setPosicion(float x, float y);
        void setHaAtacado(bool atacado);
        bool getHaAtacado();
        bool getVivo();
        bool getQuemado();
        bool getHackeado();
        int getPocion();
        int getCohete();
        int getArmadura();
        int getDano();
        int getCritico();
        int getNumPocion();
        int getNumCohete();
        Texture getTextura();
        Sprite getSprite();
        Sprite getSpriteAtaque();
        Sprite getSpriteImpacto();

        //metodos para la barra de vida
        Sprite getSpriteVida1();
        Sprite getSpriteVida2();
        RectangleShape getMarcavida();
    protected:
        bool quem;
        bool hack;
        int contq;
        int conth;
        int vida;
        int armadura;
        int dano;
        int critico;
        Texture textura;
        Texture textura2;
        Texture textura3;
        Sprite sprite;
        Sprite spriteAtaque1;
        Sprite spriteImpacto1;
        bool haAtacado;
        bool vidaColocada=false;
        bool vivo;
        int numPocion;
        int numCohete;

        //variables para la barra de vida
        float vidaini;
        Sprite spriteVida1;
        Sprite spriteVida2;
        RectangleShape marcavida;
        Texture textura4;
};

#endif
