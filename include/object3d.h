#ifndef OBJECT_3D_H
#define OBJECT_3D_H

#include "object.h" // for inheriting from Object

class Object3D : public Object
{
    friend class Chunk;

protected:
    void setBody(b2World &world, ObjectType type, b2Vec2 position, float angle);

public:
    Object3D(b2World &world, ObjectType type);
    Object3D(b2World &world, ObjectType type, b2Vec2 position, float angle);
};

#endif
