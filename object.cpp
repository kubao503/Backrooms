#include "object.h"

b2Vec2 Object::getNewPosition()
{
    static int count{0};
    int tmp{count++};
    return b2Vec2(0, tmp * 50.0f);
}

Object::Object(sf::RectangleShape shape, const b2BodyDef &bodyDef, const b2FixtureDef &fixture)
    : shape_{shape}
{
    const sf::Vector2f &size{shape_.getSize()};
    shape_.setOrigin(0.5f * size);
    shape_.scale(2.0f, 2.0f);
    body_ = world_g.CreateBody(&bodyDef);
    body_->SetTransform(getNewPosition(), 0);
    this->addFixture(fixture);
}

void Object::control()
{
    // const float VELOCITY = 2.0f;
    const float VELOCITY = 3.0f;
    b2Vec2 newVelocity(0.0f, 0.0f);

    // Moving objects
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        newVelocity += b2Vec2(0.0f, VELOCITY);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        newVelocity += b2Vec2(0.0f, -VELOCITY);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        newVelocity += b2Vec2(VELOCITY, 0.0f);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        newVelocity += b2Vec2(-VELOCITY, 0.0f);
    }

    // body_->SetLinearVelocity(newVelocity);
    setLocalVelocity(newVelocity);

    int mouseXMovement(camera_g.getMouseXMovement());
    body_->SetAngularVelocity(0.18f * mouseXMovement);
}

void Object::setLocalVelocity(const b2Vec2 &newVelocity)
{
    const float angle{body_->GetAngle() - static_cast<float>(M_PI / 2.0)};
    body_->SetLinearVelocity(b2Vec2(
        newVelocity.x * cos(angle) - newVelocity.y * sin(angle),
        newVelocity.x * sin(angle) + newVelocity.y * cos(angle)));
}