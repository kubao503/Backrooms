#ifndef OBJECT_H
#define OBJECT_H

#include "shapes.h"

#include <box2d/box2d.h>

extern b2World world_g;

class Object
{
protected:
    Shapes::Type shapeIdx_;
    b2Body *body_;

    b2Vec2 getNewPosition();

public:
    // friend void Camera::drawObject(Object &object);
    // friend void Camera::raycast(Player &object);

    Object(Shapes::Type shapeIdx, const b2BodyDef &bodyDef, const b2FixtureDef &fixture);
    void addFixture(const b2FixtureDef &fixture)
    {
        body_->CreateFixture(&fixture);
    }
    Shapes::Type getShapeIdx() { return shapeIdx_; }
    const b2Vec2 &getPosition() const { return body_->GetPosition(); };
};

#endif