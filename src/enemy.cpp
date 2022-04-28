#include "enemy.h"

void Enemy::setVelocity()
{
    // Set velocity to waypoints location
    b2Vec2 waypointDirection{getVector(getPosition(), waypoint_)};
    waypointDirection.Normalize();
    body_->SetLinearVelocity(waypointDirection);

    // b2BodyDef a;
    // b2World b(b2Vec2(0.0f, 0.0f));
    // auto ptr{std::make_unique<b2Body>(&a, &b)};
    // std::unique_ptr<b2Body> ptr2{std::move(ptr)};
}

void Enemy::updateWaypoint(const Object &player)
{
    // Check if player is visible for enemy
    // If yes - set waypoint to the player positioin
    waypoint_ = player.getPosition();
    // Check if waypoint is reached
    // If yes - set waypoint to random location
}

void Enemy::control(const Object &player)
{
    updateWaypoint(player);
    setVelocity();
}
