#include "enemy.h"

void Enemy::setVelocity()
{
    // Set velocity to waypoints location
    b2Vec2 waypointDirection{getVec(getPosition(), waypoint_)};
    waypointDirection.Normalize();
    body_->SetLinearVelocity(waypointDirection);
}

void Enemy::updateWaypoint(const Object &player)
{
    b2Vec2 ray{getVec(getPosition(), player.getPosition())};
    Ray::RayCallback rayCallback = Ray::sendRay(*body_->GetWorld(), getPosition(), ray);
    if (!rayCallback.hit())
    {
        // If player is visible for enemy set waypoint to the player positioin
        waypoint_ = player.getPosition();
    }
    else if (distance(getPosition(), waypoint_) < 0.01)
    {
        // If waypoint is reached set waypoint to random location

        b2Vec2 offsetVec{getVec(0.0f)};  // Should be random
        waypoint_ += offsetVec;
    }
}

void Enemy::control(const Object &player)
{
    if (spawned_)
    {
        updateWaypoint(player);
        setVelocity();
    }
}

void Enemy::startHunt(b2World &world, const Object &player)
{
    spawned_ = true;
    b2Vec2 offset(1.0f, 0.0f);  // Needed to not spawn enemy directly on player
    setBody(world, Type::ENEMY, player.getPosition() + offset, 0.0f);
}

void Enemy::stopHunt()
{
    spawned_ = false;
    destroyBody();
}
