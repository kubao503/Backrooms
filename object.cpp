#include "object.h"

b2Vec2 Object::getNewPosition()
{
    static int count{5};
    int tmp{count++};
    return b2Vec2(tmp * 50.0f, tmp * 50.0f);
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

void Object::rayCast()
{
    b2RayCastInput input;
    // b2Vec2 currentPosition{body_->GetPosition()};
    // currentPosition += b2Vec2(15.0f, 15.0f);
    // input.p1 = currentPosition;
    // currentPosition += b2Vec2(2.0f, 2.0f);
    // input.p2 = currentPosition;
    input.p1.Set(0.0f, 0.0f);
    input.p1.Set(10.0f, 0.0f);
    input.maxFraction = 1000.0f;
    int32 childIndex = 0;

    b2RayCastOutput output;
    b2Fixture *fix = body_->GetFixtureList();
    bool hit = fix[0].RayCast(&output, input, childIndex);
    if (hit)
        shape_.setScale(output.fraction, output.fraction);
        // std::cout << output.fraction << '\n';
}

void Object::control()
{
    // const float VELOCITY = 2.0f;
    const float VELOCITY = 3.0f;
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