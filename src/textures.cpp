#include "textures.h"

sf::Texture Textures::textures_[TOTAL]{};

bool Textures::init()
{
    return textures_[ENEMY].loadFromFile("media/enemy.png");
}