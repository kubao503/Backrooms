#ifndef OBJECT_2D_H
#define OBJECT_2D_H

#include "object.h" // for inheriting from Object

class Object2D : public Object
{
public:
    using object2Ds_t = std::vector<std::unique_ptr<Object2D>>;

    Object2D(b2World &world, ObjectType type);
    Object2D(b2World &world, ObjectType type, const b2Vec2 &position, float angle);
};

#endif
