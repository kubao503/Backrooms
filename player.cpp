#include "player.h"

void Player::control()
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

    int mouseXMovement(userio_g.getMouseXMovement());
    body_->SetAngularVelocity(0.18f * mouseXMovement);
}

void Player::setLocalVelocity(const b2Vec2 &newVelocity)
{
    const float angle{body_->GetAngle() - static_cast<float>(M_PI / 2.0)};
    body_->SetLinearVelocity(b2Vec2(
        newVelocity.x * cos(angle) - newVelocity.y * sin(angle),
        newVelocity.x * sin(angle) + newVelocity.y * cos(angle)));
}