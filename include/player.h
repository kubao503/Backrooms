#ifndef PLAYER_H
#define PLAYER_H

#include "userio.h"     // for getting mouse input
#include "object2d.h"   // for inheriting form Object2D
#include "myWorld.h"    // for creating b2Body

#include <box2d/box2d.h>    // for setting b2Body velocity

class Player : public Object2D
{
    void setLocalVelocity(const b2Vec2 &newVelocity); // Sets velocity based on the local cooridinates

public:
    Player(MyWorld &world, ObjectType objectType)
        : Object2D{world, objectType} {}

    float getAngle() const { return body_->GetAngle(); };
    void control(UserIO &userIO);
};

#endif
