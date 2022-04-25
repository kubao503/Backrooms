#include "shapes.h"

sf::RectangleShape Shapes::shapes_[Type::TOTAL]{
    shapeGenerator(sf::Vector2f(2.0f, 50.0f), sf::Color::Yellow),
    shapeGenerator(sf::Vector2f(2.0f, 50.0f), sf::Color::Red),
    shapeGenerator(sf::Vector2f(10.f, 10.f), sf::Color::Green),
    shapeGenerator(sf::Vector2f(39.0f, 80.0f), sf::Color::White)};

void Shapes::init()
{
    shapes_[ENEMY].setTexture(&Textures::getTexture(Textures::ENEMY), true);
}

sf::RectangleShape Shapes::shapeGenerator(const sf::Vector2f &size, sf::Color color)
{
    sf::RectangleShape newShape(size);
    newShape.setOrigin(size * 0.5f); // Sets origin to shape's center
    newShape.setFillColor(color);
    return newShape;
}
