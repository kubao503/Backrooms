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

    // Returns unique position helping avoiding spawning
    // objects at the same place
    b2Vec2 getNewPosition();

public:
    Object(MyWorld &world, Shapes::Type shapeIdx, const b2BodyDef &bodyDef, const b2FixtureDef &fixture);
    void addFixture(const b2FixtureDef &fixture)
    {
        body_->CreateFixture(&fixture);
    }
    Shapes::Type getShapeIdx() const { return shapeIdx_; }
    const b2Vec2 &getPosition() const { return body_->GetPosition(); };
};

#endif