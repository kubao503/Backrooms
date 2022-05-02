#ifndef OBJECT_3D_H
#define OBJECT_3D_H

#include "object.h" // for inheriting from Object
#include "myMath.h" // for rotating vectors

class Object3D : public Object
{
    friend class Chunk;

private:
    b2Vec2 *getCorners() const;

public:
    b2Vec2 getClosestCorner(const b2Vec2 &playerPos) const;
    Object3D(b2World &world, ObjectType type);
    Object3D(b2World &world, ObjectType type, const b2Vec2 &position, float angle);
};

#endif
