#ifndef OBJECT_H
#define OBJECT_H

#include "camera.h"

#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>
#include <iostream>

extern b2World world_g;
extern Camera camera_g;

class Object
{
private:
    sf::RectangleShape shape_;
    b2Body *body_;

    b2Vec2 getNewPosition();

public:
    friend void Camera::drawOnScreen(Object &object);
    friend void Camera::raycast(Object &object);

    Object(sf::RectangleShape shape, const b2BodyDef &bodyDef, const b2FixtureDef &fixture);
    void addFixture(const b2FixtureDef &fixture)
    {
        body_->CreateFixture(&fixture);
    }

    // void rayCast();
    void control();
};

#endif