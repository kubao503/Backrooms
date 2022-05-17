#include "shapes.h"

sf::RectangleShape Shapes::shapes_[Type::TOTAL]{
    shapeGenerator(sf::Vector2f(2.0f, 50.0f), sf::Color::White),
    shapeGenerator(sf::Vector2f(2.0f, 50.0f), sf::Color::Red),
    shapeGenerator(sf::Vector2f(509.0f, 798.0f), sf::Color::White),
    shapeGenerator(sf::Vector2f(1864.0f, 1051.0f), sf::Color::White, true),
    shapeGenerator(sf::Vector2f(1864.0f, 1051.0f), sf::Color::White, true),
    shapeGenerator(sf::Vector2f(1864.0f, 1051.0f), sf::Color::White, true),
    shapeGenerator(sf::Vector2f(1864.0f, 1051.0f), sf::Color::White, true),
    shapeGenerator(sf::Vector2f(1920.0f, 1080.0f), sf::Color::White, true),
    shapeGenerator(sf::Vector2f(1777.0f, 1000.0f), sf::Color::White, true)};

sf::RectangleShape Shapes::getShape(Type shapeIdx, float offset)
{
    assert(shapeIdx >= 0 && shapeIdx < TOTAL);

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
    shapes_[EMF].setTexture(&Textures::getTexture(Textures::EMF));
    shapes_[EMF1].setTexture(&Textures::getTexture(Textures::EMF1));
    shapes_[EMF2].setTexture(&Textures::getTexture(Textures::EMF2));
    shapes_[EMF3].setTexture(&Textures::getTexture(Textures::EMF3));
    shapes_[FLASHLIGHT].setTexture(&Textures::getTexture(Textures::FLASHLIGHT));
    shapes_[BACKGROUND].setTexture(&Textures::getTexture(Textures::BACKGROUND));
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
