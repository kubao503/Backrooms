#include "shapes.h"

sf::RectangleShape Shapes::shapes_[Type::TOTAL]{
    shapeGenerator(sf::Vector2f(2.0f, 50.0f), sf::Color::White),
    shapeGenerator(sf::Vector2f(2.0f, 50.0f), sf::Color::Red),
    shapeGenerator(sf::Vector2f(195.0f, 400.0f), sf::Color::White)};

sf::RectangleShape Shapes::getShape(Type shapeIdx, float offset)
{
    if (shapeIdx >= TOTAL)
        throw "Invalid shapeIdx\n";

    if (shapes_[shapeIdx].getTexture())
    {
        constexpr float offsetFactor{10.0f};

        sf::Vector2f shapeSize = shapes_[shapeIdx].getSize();
        sf::Vector2u textureSize = shapes_[shapeIdx].getTexture()->getSize();
        unsigned int offsetMod{static_cast<int>(shapeSize.x * offset * offsetFactor) % textureSize.x};

        shapes_[shapeIdx].setTextureRect(sf::IntRect(
            sf::Vector2i(offsetMod, 0),
            sf::Vector2i(shapeSize.x, textureSize.y)));
    }
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
