#ifndef ITEM_H
#define ITEM_H

#include "object2d.h"

class Item : public Object2D
{
protected:
    Shapes::Type GUIShapeIdx_;

public:
    using Object::destroyBody;

    Shapes::Type getGUIShapeIdx() const { return GUIShapeIdx_; }

    Item(b2World &world, Type type, Shapes::Type GUIShapeIdx, const b2Vec2 &position, float angle);

    virtual void action(const b2Vec2 &playerPos) = 0;
    virtual void drop(b2World &world, const Object &player) = 0;
};

#endif
