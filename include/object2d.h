#ifndef OBJECT_2D_H
#define OBJECT_2D_H

#include "object.h" // for inheriting from Object

class Object2D : public Object
{
public:
    Object2D(b2World &world, ObjectType type);
    Object2D(b2World &world, ObjectType type, b2Vec2 position, float angle);
};

#endif
