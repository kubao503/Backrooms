#include "userio.h"

void UserIO::drawOnScreen(Shapes::Type shapeIdx, float x, float y, float xScale, float yScale)
{
    sf::Vector2u size{window_.getSize()};
    sf::RectangleShape shape{Shapes::getShape(shapeIdx)};
    shape.setScale(xScale, yScale);
    shape.setPosition(x + size.x / 2.0f, y + size.y / 2.0f);
    window_.draw(shape);
}

void UserIO::drawObject(Object &object)
{
    const b2Vec2 &currentPosition = object.getPosition();
    drawOnScreen(object.getShapeIdx(), currentPosition.x, currentPosition.y);
}

void UserIO::handleEvents()
{
    sf::Event event;
    while (window_.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            window_.close();
    }
}

int UserIO::getMouseXMovement()
{
    static const sf::Vector2i defaultPosition(100, 100);
    int mouseMovement{sf::Mouse::getPosition(window_).x - defaultPosition.x};
    sf::Mouse::setPosition(defaultPosition, window_);
    return mouseMovement;
}