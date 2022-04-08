#ifndef OBJECT_H
#define OBJECT_H

#include "camera.h"

#include <box2d/box2d.h>
#include <SFML/Graphics.hpp>
#include <iostream>

extern b2World world_g;

class Object
{
private:
    sf::RectangleShape shape_;
    b2Body *body_;

    b2Vec2 getNewPosition()
    {
        static int count{0};
        return b2Vec2(count++ * 20.0f, 0.0f);
    }

public:
    friend void Camera::drawOnScreen(Object &object);

    Object(sf::RectangleShape shape, const b2BodyDef &bodyDef)
        : shape_{shape}
    {
        body_ = world_g.CreateBody(&bodyDef);
        body_->SetTransform(getNewPosition(), 0);
    }

    void addFixture(const b2FixtureDef &fixture)
    {
        body_->CreateFixture(&fixture);
    }

    void control();
};

#endif