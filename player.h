#ifndef PLAYER_H
#define PLAYER_H

#include "userio.h"
#include "object.h"
#include "myWorld.h"

#include <box2d/box2d.h>

class Player : public Object
{
    void setLocalVelocity(const b2Vec2 &newVelocity); // Sets velocity based on the local cooridinates

public:
    Player(MyWorld &world, Shapes::Type shapeIdx, const b2BodyDef &bodyDef, const b2FixtureDef &fixture)
        : Object{world, shapeIdx, bodyDef, fixture} {}
    Player(MyWorld &world, ObjectType objectType)
        : Object{Object::objectGenerator(world, objectType)} {}

    float getAngle() const { return body_->GetAngle(); };
    void control(UserIO &userIO);
};

#endif
