#ifndef TEXTURES_H
#define TEXTURES_H

#include <SFML/Graphics.hpp> // for using sf::Texture

class Textures
{
public:
    enum Type
    {
        ENEMY,
        WALL,
        WALKIETALKIE,
        TOTAL
    };
    static bool init();
    static const sf::Texture &getTexture(Type textureType)
    {
        return textures_[textureType];
    }

private:
    static sf::Texture textures_[TOTAL];
};

#endif
