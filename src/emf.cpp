#include "emf.h"

Emf::Emf(b2World &world, const b2Vec2 &position, float angle)
    : Item{world, emfShapes_[0], position, angle} {}

void Emf::action(const b2World &world, const Player &player)
{
    // if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
    //     on_ = !on_;
    // GUIShapeIdx_ = emfShapes_[on_];

    b2AABB aabb;
    aabb.upperBound = player.getPosition() + b2Vec2(aabbSize, aabbSize);
    aabb.lowerBound = player.getPosition() - b2Vec2(aabbSize, aabbSize);

    EnemyCallback callback;
    world.QueryAABB(&callback, aabb);

    // Calculating distance to enemy
    if (callback.getEnemy())
    {
        GUIShapeIdx_ = emfShapes_[1];
    }
    else
    {
        GUIShapeIdx_ = emfShapes_[0];
    }
}

bool Emf::EnemyCallback::ReportFixture(b2Fixture *fixture)
{
    Object *obj = (Object *)fixture->GetBody()->GetUserData().pointer;
    Enemy *enemy = dynamic_cast<Enemy *>(obj);

    if (enemy)
    {
        foundEnemy_ = enemy;
        return false; // Stop on the first enemy
    }

    return true; // Keep searching for enemy
}
