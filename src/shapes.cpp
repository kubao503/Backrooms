#include "shapes.h"

sf::RectangleShape Shapes::shapes_[Type::TOTAL]{
    shapeGenerator(sf::Vector2f(2.0f, 50.0f), sf::Color::White),
    shapeGenerator(sf::Vector2f(2.0f, 50.0f), sf::Color::Red),
    shapeGenerator(sf::Vector2f(195.0f, 400.0f), sf::Color::White),
    shapeGenerator(sf::Vector2f(1864.0f, 1051.0f), sf::Color::White, true)};

sf::RectangleShape Shapes::getShape(Type shapeIdx, float offset)
{
    if (shapeIdx < 0 || shapeIdx >= TOTAL)
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
    shapes_[ENEMY].setTexture(&Textures::getTexture(Textures::ENEMY));
    shapes_[WALL].setTexture(&Textures::getTexture(Textures::WALL));
    shapes_[WALKIETALKIE].setTexture(&Textures::getTexture(Textures::WALKIETALKIE));
}

void Shapes::scaleBasedOnScreen(sf::Shape &shape)
{
    float xScaleFactor{Conf::windowWidth / 1000.f};
    shape.scale(xScaleFactor, 1.0f);
}

void Shapes::makeFullScreen(sf::RectangleShape &shape)
{
    sf::Vector2f shapeSize{shape.getSize()};
    shape.setScale(Conf::windowWidth / shapeSize.x, Conf::windowHeight / shapeSize.y);
}

sf::RectangleShape Shapes::shapeGenerator(const sf::Vector2f &size, sf::Color color, bool fullScreen)
{
    sf::RectangleShape newShape(size);
    newShape.setOrigin(size * 0.5f); // Sets origin to shape's center
    newShape.setFillColor(color);
    scaleBasedOnScreen(newShape);
    if (fullScreen)
        makeFullScreen(newShape);
    return newShape;
}
