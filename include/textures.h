#ifndef TEXTURES_H
#define TEXTURES_H

#include <SFML/Graphics.hpp>    // for using sf::Texture

class Textures
{
public:
    enum Type
    {
        ENEMY,
        TOTAL
    };
    static bool init();
private:
    static sf::Texture textures_[TOTAL];
};

#endif