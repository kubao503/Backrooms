#include "enemy.h"

void Enemy::setVelocity()
{
    // Set velocity to waypoints location
    b2Vec2 waypointDirection{getVector(getPosition(), waypoint_)};
    waypointDirection.Normalize();
    body_->SetLinearVelocity(waypointDirection);
}

void Enemy::updateWaypoint(const Object &player)
{
    b2Vec2 ray{getVector(getPosition(), player.getPosition())};
    Camera::MyCallback rayCallback = Camera::sendRay(*body_->GetWorld(), getPosition(), ray);
    if (!rayCallback.hit())
    {
        // If player is visible for enemy set waypoint to the player positioin
        waypoint_ = player.getPosition();
    }
    else if (distance(getPosition(), waypoint_) < 0.01)
    {
        // If waypoint is reached set waypoint to random location

        b2Vec2 offsetVec{getVector(0.0f)};  // Should be random
        waypoint_ += offsetVec;
    }
}

void Enemy::control(const Object &player)
{
    updateWaypoint(player);
    setVelocity();
}
