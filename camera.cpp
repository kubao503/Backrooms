#include "camera.h"
#include "object.h"

void Camera::drawOnScreen(Object &object)
{
    const b2Vec2 &currentPosition = object.body_->GetPosition();
    drawOnScreen(object.shape_, currentPosition.x, currentPosition.y);
}

void Camera::handleEvents()
{
    sf::Event event;
    while (window_.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            window_.close();
    }
}