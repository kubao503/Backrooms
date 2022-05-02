#ifndef ITEM_H
#define ITEM_H

#include "object2d.h"

class Item : public Object2D
{
public:
    Item(b2World &world, Object::ObjectType type, const b2Vec2 &position, float angle)
        : Object2D{world, type, position, angle}
    {
        setSensor(true);
    }
};

#endif
