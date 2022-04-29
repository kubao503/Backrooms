#ifndef ENEMY_H
#define ENEMY_H

#include "object2d.h" // for inheriting from Object2D
#include "camera.h"   // for ray sending to check player visibility

#include <iostream> // DEBUG

class Enemy : public Object2D
{
    // Destination where enemy is currently going
    b2Vec2 waypoint_;

    bool spawned_{true};

    // Sets velocity for current waypoint
    void setVelocity();

    // Updated waypoint to player's position
    // only when player is visible
    void updateWaypoint(const Object &player);

public:
    Enemy(MyWorld &world, ObjectType type, b2Vec2 position, float angle)
        : Object2D{world, type, position, angle} {}

    void control(const Object &player);
    void startHunt(MyWorld &world, const Object &player);
    void stopHunt();

    bool spawned() const { return spawned_; }
};

#endif
