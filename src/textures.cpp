#include "textures.h"

sf::Texture Textures::textures_[TOTAL]{};

bool Textures::init()
{
    bool success{true};
    success = success && textures_[ENEMY].loadFromFile("media/enemy.png");
    success = success && textures_[WALL].loadFromFile("media/concrete_texture.jpg");
    return success;
}
