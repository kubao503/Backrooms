#ifndef SHAPES_H
#define SHAPES_H

#include <SFML/Graphics.hpp>    // for using sf::Shape

class Shapes
{
public:
    enum Type
    {
        WALL,
        RED_WALL,
        PLAYER,
        ENEMY,
        TOTAL
    };

    static sf::RectangleShape getShape(Type shapeIdx)
    {
        return shapes_[shapeIdx];
    }

private:
    static sf::RectangleShape shapes_[Type::TOTAL];
    static sf::RectangleShape shapeGenerator(const sf::Vector2f &size, sf::Color color);
};

#endif