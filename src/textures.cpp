#include "textures.h"

sf::Texture Textures::textures_[TOTAL]{};

bool Textures::init()
{
    bool success{true};
    success = success && textures_[ENEMY].loadFromFile("media/enemy.png");
    success = success && textures_[WALL].loadFromFile("media/concrete_texture.jpg");
    success = success && textures_[EMF].loadFromFile("media/emf.png");
    success = success && textures_[EMF1].loadFromFile("media/emf1.png");
    success = success && textures_[EMF2].loadFromFile("media/emf2.png");
    success = success && textures_[EMF3].loadFromFile("media/emf3.png");
    return success;
}
