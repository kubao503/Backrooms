#ifndef TEXTURES_H
#define TEXTURES_H

#include <SFML/Graphics.hpp>

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