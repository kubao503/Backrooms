#include "shapes.h"

sf::RectangleShape Shapes::shapes_[Type::TOTAL]{
    shapeGenerator(sf::Vector2f(2.0f, 50.0f), sf::Color::Yellow),
    shapeGenerator(sf::Vector2f(10.f, 10.f), sf::Color::Green)
    //     sf::RectangleShape wallTexture(sf::Vector2f(2.0f, 50.0f));
    // wallTexture.setOrigin(1.0f, 25.0f);
    // wallTexture.setFillColor(sf::Color::Yellow);

    //     const sf::Vector2f &size{shape_.getSize()};
    // shape_.setOrigin(0.5f * size);
    // shape_.scale(2.0f, 2.0f);
};

void Shapes::init()
{
}

sf::RectangleShape Shapes::shapeGenerator(const sf::Vector2f &size, sf::Color color)
{
    sf::RectangleShape newShape(size);
    newShape.setOrigin(size * 0.5f);
    newShape.setFillColor(color);
    return newShape;
}