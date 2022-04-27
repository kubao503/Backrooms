#ifndef OBJECT_3D_H
#define OBJECT_3D_H

#include "object.h" // for inheriting from Object

class Object3D : public Object
{
private:
    std::unique_ptr<b2Body> createBody(const b2BodyDef &bd, MyWorld &world) const override;

public:
    Object3D(MyWorld &world, ObjectType type);
    Object3D(MyWorld &world, ObjectType type, b2Vec2 position, float angle);
};

#endif