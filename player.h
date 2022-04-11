#ifndef PLAYER_H
#define PLAYER_H

#include "userio.h"
#include "object.h"

#include <box2d/box2d.h>

extern UserIO userio_g;

class Player : public Object
{
    void setLocalVelocity(const b2Vec2 &newVelocity); // Sets velocity based on the local cooridinates

public:
    Player(Shapes::Type shapeIdx, const b2BodyDef &bodyDef, const b2FixtureDef &fixture)
        : Object{shapeIdx, bodyDef, fixture} {}

    float getAngle() const { return body_->GetAngle(); };
    void control();
};

#endif
