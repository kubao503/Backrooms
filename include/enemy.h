#ifndef ENEMY_H
#define ENEMY_H

#include "object2d.h" // for inheriting from Object2D
#include "world.h"    // for getting openChunk waypoints
#include "ray.h"      // for ray sending to check player visibility

class Enemy : public Object2D
{
    // Destination where enemy is currently going
    b2Vec2 waypoint_;

    bool spawned_{true};

    // Sets velocity for current waypoint
    void setVelocity();

    // Updated waypoint to player's position
    // only when player is visible
    void updateWaypoint(const Object &player, const World &gameMap);

    World::Directions direction = World::Directions::N;

public:
    Enemy(b2World &world, b2Vec2 position, float angle)
        : Object2D{world, Type::ENEMY, position, angle} {}

    void control(const Object &player, const World &gameMap);
    void startHunt(b2World &world, const Object &player);
    void stopHunt();

    bool spawned() const { return spawned_; }
};

#endif
