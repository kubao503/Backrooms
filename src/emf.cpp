#include "emf.h"

Emf::Emf(b2World &world, const b2Vec2 &position, float angle, Mediator& mediator, const Enemy &enemy)
    : Item{world, Type::EMF, position, angle, emfShapes_[0], mediator}, enemy_{enemy} {}

void Emf::drop(b2World &world, const Object &player)
{
    setBody(world, Type::EMF, player.getPosition() + 5.0f * getVecN(player.getAngle()), 0);
    setSensor(true);

    addFixture(Type::ITEM_PICK_AREA, Category::ITEM_PICK_AREA, true);
}

void Emf::action(const b2Vec2 &playerPos)
{
    // Set default emf state
    GUIShapeIdx_ = emfShapes_.at(0);

    // Updating emf state
    if (enemy_.spawned())
    {
        float distanceToEnemy{distance(playerPos, enemy_.getPosition())};
        int stateIdx{static_cast<int>((1.f - statesNumber) / detectionRadius * distanceToEnemy + statesNumber)};
        GUIShapeIdx_ = emfShapes_.at(std::max(0, stateIdx));
    }
}
