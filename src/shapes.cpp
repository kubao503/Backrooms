#include "shapes.h"

sf::RectangleShape Shapes::shapes_[Type::TOTAL]{
    shapeGenerator(sf::Vector2f(2.0f, 50.0f), sf::Color::White),
    shapeGenerator(sf::Vector2f(2.0f, 50.0f), sf::Color::Red),
    shapeGenerator(sf::Vector2f(10.f, 10.f), sf::Color::Green),
    shapeGenerator(sf::Vector2f(195.0f, 400.0f), sf::Color::White)};

sf::RectangleShape Shapes::getShape(Type shapeIdx, int offset)
{
    if (shapeIdx >= TOTAL)
        throw "Invalid shapeIdx\n";

    sf::Vector2f shapeSize = shapes_[shapeIdx].getSize();
    shapes_[shapeIdx].setTextureRect(sf::IntRect(
        sf::Vector2i(shapeSize.x * offset, 0),
        static_cast<sf::Vector2i>(shapeSize)));
    return shapes_[shapeIdx];
}

void Shapes::init()
{
    shapes_[ENEMY].setTexture(&Textures::getTexture(Textures::ENEMY), false);
    sf::Vector2f wallSize = shapes_[WALL].getSize();
    shapes_[WALL].setTexture(&Textures::getTexture(Textures::WALL));
    shapes_[WALL].setTextureRect(sf::IntRect(
        sf::Vector2i(0, 0),
        static_cast<sf::Vector2i>(wallSize)));
}

sf::RectangleShape Shapes::shapeGenerator(const sf::Vector2f &size, sf::Color color)
{
    sf::RectangleShape newShape(size);
    newShape.setOrigin(size * 0.5f); // Sets origin to shape's center
    newShape.setFillColor(color);
    return newShape;
}
