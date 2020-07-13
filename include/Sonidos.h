#ifndef SONIDOS_H
#define SONIDOS_H
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>

class Sonidos
{
    public:
        Sonidos();
        void crear(sf::String cadena);
        void sonar();
        void pausar();

        void PlaySound(int x);
        virtual ~Sonidos();
    protected:
    private:
        sf::SoundBuffer buffer;
        sf::Sound sound;

        sf::Sound agujeroSound;
        sf::SoundBuffer agujeroBuffer;

        sf::Sound keySound;
        sf::SoundBuffer keyBuffer;

        sf::Sound puertaSound;
        sf::SoundBuffer puertaBuffer;

        sf::Sound pauseSound;
        sf::SoundBuffer pauseBuffer;

        sf::Sound jumpSound;
        sf::SoundBuffer jumpBuffer;

        sf::Sound powerUpSound;
        sf::SoundBuffer powerUpBuffer;

         sf::Sound menuSound;
        sf::SoundBuffer menuBuffer;

        sf::Sound fuenteSound;
        sf::SoundBuffer fuenteBuffer;

        sf::Sound katanaSound;
        sf::SoundBuffer katanaBuffer;
        sf::Sound disparoSound;
        sf::SoundBuffer disparoBuffer;
        sf::Sound hackeoSound;
        sf::SoundBuffer hackeoBuffer;
        sf::Sound inyeccionSound;
        sf::SoundBuffer inyeccionBuffer;
        sf::Sound ultiSound;
        sf::SoundBuffer ultiBuffer;

        sf::Sound enemigosSound;
        sf::SoundBuffer enemigosBuffer;

        sf::Sound seleccionenemigosSound;
        sf::SoundBuffer seleccionenemigosBuffer;

        sf::Sound loadSound;
        sf::SoundBuffer loadBuffer;

        int musica;
        int sonido;
        int tipo;
};

#endif // SONIDOS_H
