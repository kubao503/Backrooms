#include "object.h"

b2Vec2 Object::getNewPosition()
{
    static int count{1};
    int tmp{count++};
    return b2Vec2(tmp * 50.0f, tmp * 50.0f);
}

Object::Object(sf::RectangleShape shape, const b2BodyDef &bodyDef)
    : shape_{shape}
{
    const sf::Vector2f &size{shape_.getSize()};
    shape_.setOrigin(0.5f * size);
    shape_.scale(2.0f, 2.0f);
    body_ = world_g.CreateBody(&bodyDef);
    body_->SetTransform(getNewPosition(), 0);
}

void Object::control()
{
    const float VELOCITY = 2.0f;
    b2Vec2 newVelocity(0.0f, 0.0f);

    // Moving objects
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        newVelocity += b2Vec2(0.0f, -VELOCITY);
        // body_->SetLinearVelocity(b2Vec2(0.0f, -VELOCITY));
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        newVelocity += b2Vec2(0.0f, VELOCITY);
        // body_->SetLinearVelocity(b2Vec2(0.0f, VELOCITY));
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        newVelocity += b2Vec2(-VELOCITY, 0.0f);
        // body_->SetLinearVelocity(b2Vec2(-VELOCITY, 0.0f));
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        newVelocity += b2Vec2(VELOCITY, 0.0f);
        // body_->SetLinearVelocity(b2Vec2(VELOCITY, 0.0f));
    }
    // if (!sf::Keyboard::isKeyPressed(sf::Keyboard::W) && !sf::Keyboard::isKeyPressed(sf::Keyboard::S) && !sf::Keyboard::isKeyPressed(sf::Keyboard::A) && !sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    // body_->SetLinearVelocity(b2Vec2(0.0f, 0.0f));
    body_->SetLinearVelocity(newVelocity);
}