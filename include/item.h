#ifndef ITEM_H
#define ITEM_H

#include "object2d.h"
#include "component.h"

class Item : public Object2D, public Component
{
protected:
    Shapes::Type GUIShapeIdx_;

public:
    using Object::destroyBody;

    Shapes::Type getGUIShapeIdx() const { return GUIShapeIdx_; }

    Item(b2World &world, Type type, const b2Vec2 &position, float angle, Shapes::Type GUIShapeIdx, Mediator &mediator);

    virtual void action(const b2Vec2 &playerPos) = 0;
    virtual void drop(b2World &world, const Object &player) = 0;
};

#endif
