#include "emf.h"

Emf::Emf(b2World &world, const b2Vec2 &position, float angle)
    : Item{world, Type::EMF, emfShapes_[0], position, angle} {}

void Emf::drop(b2World &world, const Object &player)
{
    setBody(world, Type::EMF, player.getPosition() + 5.0f * getVecN(player.getAngle()), 0);
}

void Emf::action(const b2World &world, const Object &player)
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
        float distanceToEnemy{distance(player.getPosition(), callback.getEnemy()->getPosition())};
        int stateIdx{static_cast<int>(-3.0f / aabbSize * distanceToEnemy + emfStates)};
        GUIShapeIdx_ = emfShapes_[stateIdx];
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
