#include "object2d.h"

std::unique_ptr<b2Body> Object2D::createBody(const b2BodyDef &bd, MyWorld &world) const
{
    return std::unique_ptr<b2Body>(world.b2World::CreateBody(&bd));
}

Object2D::Object2D(MyWorld &world, ObjectType type)
    : Object{type}
{
    setBody(world, type);
}