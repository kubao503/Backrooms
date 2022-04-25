#include "object3d.h"

std::unique_ptr<b2Body> Object3D::createBody(const b2BodyDef &bd, MyWorld &world) const
{
    return world.CreateBody(&bd, *this);
}

Object3D::Object3D(MyWorld &world, ObjectType type)
    : Object{type}
{
    setBody(world, type);
}