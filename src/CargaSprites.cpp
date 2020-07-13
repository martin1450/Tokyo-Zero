#include "CargaSprites.h"

using namespace sf;

CargaSprites* CargaSprites::Instancia = nullptr;

CargaSprites::CargaSprites() {

    // Solo permite una instancia, en otro caso lanza excepcion

    assert(Instancia == nullptr); // Assert es una macro que aborta si da false. Si da true, no pasa nada
    Instancia = this;
}

Texture& CargaSprites::getTexture(std::string const& archivo) {

    auto& mapaTexturas = Instancia->m_Texturas;
    auto coincidencia = mapaTexturas.find(archivo);  // Mira si ya está cargada la textura

    if (coincidencia != mapaTexturas.end()) {   // Si no llega al final es porque lo ha encontrado

        return coincidencia->second;    // Devuelve el par (valor)
    }
    else {                                      // Si no lo ha encontrado

        auto& textura = mapaTexturas[archivo];      // Crea esa textura en el mapa
        textura.loadFromFile(archivo);              // Carga la textura
        textura.setSmooth(true);                    // Suaviza la textura
        return textura;                             // Y la devuelve
    }
}
