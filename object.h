#ifndef OBJECT_H
#define OBJECT_H

#include "shapes.h"
#include "myWorld.h"

#include <box2d/box2d.h>

// extern MyWorld world_g;

class Object
{
protected:
    Shapes::Type shapeIdx_;
    MyBody *body_{nullptr};

    b2Vec2 getNewPosition();

public:
    // friend void Camera::drawObject(Object &object);
    // friend void Camera::raycast(Player &object);

    Object(MyWorld &world, Shapes::Type shapeIdx, const b2BodyDef &bodyDef, const b2FixtureDef &fixture);
    void addFixture(const b2FixtureDef &fixture)
    {
        body_->CreateFixture(&fixture);
    }
    Shapes::Type getShapeIdx() { return shapeIdx_; }
    const b2Vec2 &getPosition() const { return body_->GetPosition(); };
};

#endif