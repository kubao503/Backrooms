#include "camera.h"
#include "object.h"

void Camera::drawOnScreen(sf::Shape &shape, float x, float y)
{
    sf::Vector2u size{window_.getSize()};
    shape.setPosition(x + size.x / 2.0f, y + size.y / 2.0f);
    window_.draw(shape);
}

void Camera::raycast(Object &object)
{
    // Crate ray vector based on object position
    const b2Vec2 &position{object.body_->GetPosition()};
    b2RayCastInput input;
    input.p1 = input.p2 = position;
    input.p2 += b2Vec2(0.0f, 50.0f);
    input.maxFraction = 3;

    float smallestFraction{input.maxFraction};

    // iterate over all bodies and raycast them
    for (b2Body *b = world_g.GetBodyList(); b; b = b->GetNext())
    {
        b2RayCastOutput output;
        b2Fixture *fixList{b->GetFixtureList()};
        bool hit{fixList[0].RayCast(&output, input, 0)};

        // if a body is hit, check if this is the closest hit
        if (hit && output.fraction < smallestFraction)
        {
            smallestFraction = output.fraction;
        }
    }

    // Calculate the closes hit point
    b2Vec2 hitPoint{input.p1 + smallestFraction * (input.p2 - input.p1)};

    if (smallestFraction != input.maxFraction)
    {
        // Draw the closest hit point
        sf::RectangleShape wallTexture(sf::Vector2f(10.0f, 50.0f));
        wallTexture.setOrigin(5.0f, 25.0f);
        wallTexture.setFillColor(sf::Color::Yellow);
        wallTexture.setScale(1, 1.0f / smallestFraction);
        camera_g.drawOnScreen(wallTexture, 0, 0);
    }
}

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