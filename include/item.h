#ifndef ITEM_H
#define ITEM_H

#include "object2d.h"

class Item : public Object2D
{
public:
    using Object::destroyBody;

    Item(b2World &world, const b2Vec2 &position, float angle)
        : Object2D{world, Type::ITEM, position, angle}
    {
        setSensor(true);
    }
};

#endif
