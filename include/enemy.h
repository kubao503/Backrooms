#ifndef ENEMY_H
#define ENEMY_H

#include "object2d.h"
#include "myMath.h"

class Enemy : public Object2D
{
    // Destination where player was last seen
    b2Vec2 waypoint_;

    // Sets velocity for current waypoint
    void setVelocity();
    void updateWaypoint(const Object &player);

public:
    Enemy(MyWorld &world, ObjectType type, b2Vec2 position, float angle)
        : Object2D{world, type, position, angle} {}

    void control(const Object &player);
};

#endif
