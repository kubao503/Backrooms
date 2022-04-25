#include "userio.h"

void UserIO::drawOnScreen(Shapes::Type shapeIdx, float x, float y, float xScale, float yScale, float dim)
{
    sf::Vector2u size{window_.getSize()};
    sf::RectangleShape shape{Shapes::getShape(shapeIdx)};
    const sf::Color &originalColor = shape.getFillColor();
    shape.setFillColor(std::move(dimColor(originalColor, dim)));
    shape.setScale(xScale, yScale);

    shape.setPosition(size.x / 2.0f * (x + 1.0f), size.y / 2.0f * (y + 1.0f));
    window_.draw(shape);
    shape.setFillColor(originalColor);
}

sf::Color UserIO::dimColor(const sf::Color &color, float dimFactor)
{
    dimFactor = std::min(dimFactor, 1.0f);
    return sf::Color(color.r * dimFactor,
                     color.g * dimFactor,
                     color.b * dimFactor,
                     color.a);
}

void UserIO::handleEvents()
{
    sf::Event event;
    while (window_.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            window_.close();
        if (event.type == sf::Event::LostFocus)
            focus_ = false;
        if (event.type == sf::Event::GainedFocus)
        {
            focus_ = true;
            getMouseXMovement();    // Reseting mouse position
        }
    }
}

int UserIO::getMouseXMovement()
{
    if (!focus_)    // Don't turn around if user is not focused on the window
        return 0;
    static const sf::Vector2i defaultPosition(100, 100);
    int mouseMovement{sf::Mouse::getPosition(window_).x - defaultPosition.x};
    sf::Mouse::setPosition(defaultPosition, window_);
    return mouseMovement;
}