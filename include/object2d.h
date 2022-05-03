#ifndef OBJECT_2D_H
#define OBJECT_2D_H

#include "drawableObject.h" // for inheriting from Object

class Object2D : public DrawableObject
{
public:
    Object2D(b2World &world, Type type, const b2Vec2 &position, float angle);
};

#endif
