#include "enemy.h"

void Enemy::setVelocity()
{
    // Set velocity to waypoints location
    b2Vec2 waypointDirection{getVec(getPosition(), waypoint_)};
    waypointDirection.Normalize();
    body_->SetLinearVelocity(waypointDirection);
}

void Enemy::updateWaypoint(const b2Vec2 &playerPos, const World &gameMap, bool debug)
{
    b2Vec2 ray{getVec(getPosition(), playerPos)};
    Ray::RayCallback rayCallback = Ray::sendRay(*body_->GetWorld(), getPosition(), ray);
    if (!rayCallback.hit() && !debug) // DEBUG
    {
        // If player is visible for enemy set waypoint to the player positioin
        waypoint_ = playerPos;
    }
    else if (distance(getPosition(), waypoint_) < 0.01)
    {
        // If waypoint is reached set waypoint to random location
        const b2Vec2 &newWaypoint{gameMap.openChunk(getPosition(), direction)};
        if (newWaypoint.IsValid())
            waypoint_ = newWaypoint;
    }
}

void Enemy::control(const b2Vec2 &playerPos, const World &gameMap, bool debug)
{
    if (spawned_)
    {
        updateWaypoint(playerPos, gameMap, debug);
        setVelocity();
    }
}

void Enemy::startHunt(b2World &world, const Object &player)
{
    spawned_ = true;
    b2Vec2 offset(1.0f, 0.0f); // Needed to not spawn enemy directly on player
    setBody(world, Type::ENEMY, player.getPosition() + offset, 0.0f);
}

void Enemy::stopHunt()
{
    spawned_ = false;
    destroyBody();
}