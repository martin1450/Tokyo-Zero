#include "LevelFactory.h"
#include <iostream>
#include <cstring>
#include "TileMap.h"
#include "Ventana.h"
#include "tinyxml2.h"

LevelFactory::LevelFactory()
{
    nivel = 1;
}

void LevelFactory::inicializar(){

    switch (nivel){
        case 1:
            cadena = "mapas/tilemaps/mapa1.xml";
            imagen = "mapas/tilesheet.png";
            fondo = "mapas/fondo 3.png";
            break;
        case 2:
            cadena = "mapas/tilemaps/mapa2.xml";
            imagen = "mapas/tilesheet1.png";
            fondo = "mapas/fondo 1.png";
            break;
        case 3:
            cadena = "mapas/tilemaps/mapa2..xml";
            imagen = "mapas/tilesheet1.png";
            fondo = "mapas/fondo 2.png";
            break;
        case 4:
            cadena = "mapas/tilemaps/mapa3..xml";
            imagen = "mapas/tilesheet2.4.png";
            fondo = "mapas/fondo 3.png";
            break;
        case 5:
            cadena = "mapas/tilemaps/mapa4.xml";
            imagen = "mapas/tilesheet3.2.png";
            fondo = "mapas/fondo 4.png";
            break;
    }

    Ventana::getInstancia()->fondoTexture.loadFromFile(fondo.c_str());
    Ventana::getInstancia()->fondo.setTexture(Ventana::getInstancia()->fondoTexture);
    Ventana::getInstancia()->fondo.setOrigin(1920/2,1080/2);
    Ventana::getInstancia()->fondo.setPosition(1920/2, 1056/2);

    tinyxml2::XMLDocument doc;
    tinyxml2::XMLError result = doc.LoadFile( cadena.c_str() );

    if (result != tinyxml2::XML_SUCCESS) {
        std::cerr << "Error cargando la imagen";
        exit(0);
        }

    tinyxml2::XMLElement *element = doc.FirstChildElement("map");
    std::string gid;
    std::string gid2;
    int width = std::stoi(element->Attribute("width"));
    int height = std::stoi(element->Attribute("height"));
    int gids [width*height];
    int gids2 [width*height];
    int i = 0;

    element = doc.FirstChildElement("map")->FirstChildElement("layer")->FirstChildElement("data");
    for(tinyxml2::XMLElement* child=element->FirstChildElement(); child != NULL; child=child->NextSiblingElement())
    {
        gid = child->Attribute("gid");
       // std::cout<<gid<<std::endl;
        gids[i] = std::stoi(gid)-1;
        ++i;
    }
    i=0;
    element = doc.FirstChildElement("map")->FirstChildElement("layer");
    element = element->NextSiblingElement("layer")->FirstChildElement("data");
    for(tinyxml2::XMLElement* child2=element->FirstChildElement(); child2 != NULL; child2=child2->NextSiblingElement())
    {
        gid2 = child2->Attribute("gid");
        gids2[i] = std::stoi(gid2)-1;
        ++i;
    }
    //create the tilemap from the level definition
    i=0;
    element = doc.FirstChildElement("map")->FirstChildElement("layer");
    element = element->NextSiblingElement("layer");
    element = element->NextSiblingElement("layer")->FirstChildElement("data");
    for(tinyxml2::XMLElement* child2=element->FirstChildElement(); child2 != NULL; child2=child2->NextSiblingElement())
    {
        gid2 = child2->Attribute("gid");
        Ventana::getInstancia()->colisones[i] = std::stoi(gid2)-1;
        ++i;
    }


   if (!map.load(imagen.c_str(), sf::Vector2u(32, 32), gids, width, height))
        std::cerr << "Error cargando el mapa1";

    if (!map2.load(imagen.c_str(), sf::Vector2u(32, 32), gids2, width, height))
        std::cerr << "Error cargando el mapa2";

}


void LevelFactory::pintarse(){

    Ventana::getInstancia()->window.draw(map);
    Ventana::getInstancia()->window.draw(map2);
}

LevelFactory::~LevelFactory()
{
    //dtor
}
