#ifndef SHAPES_H
#define SHAPES_H

#include <SFML/Graphics.hpp> // for using sf::Shape
#include "textures.h"        // for setting sf::Texture

class Shapes
{
public:
    enum Type
    {
        WALL,
        RED_WALL,
        ENEMY,
        WALKIETALKIE,
        TOTAL
    };

    static sf::RectangleShape getShape(Type shapeIdx, float offset = 0.0f);

    // Adds textures to some shapes
    static void init();

private:
    static sf::RectangleShape shapes_[Type::TOTAL];
    static sf::RectangleShape shapeGenerator(const sf::Vector2f &size, sf::Color color);
};

#endif
