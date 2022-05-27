#ifndef TEXTURES_H
#define TEXTURES_H

#include <SFML/Graphics.hpp> // for using sf::Texture
#include <cassert>          // for checking texture type

class Textures
{
public:
    enum Type
    {
        ENEMY,
        WALL,
        EMF,
        EMF1,
        EMF2,
        EMF3,
        FLASHLIGHT,
        BACKGROUND,
        TOTAL
    };
    static bool init();
    static const sf::Texture &getTexture(Type textureType)
    {
        assert(textureType >= 0 && textureType < TOTAL);

        return textures_[textureType];
    }

private:
    static sf::Texture textures_[TOTAL];
};

#endif
