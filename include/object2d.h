#ifndef OBJECT_2D_H
#define OBJECT_2D_H

#include "object.h" // for inheriting from Object

class Object2D : public Object
{
private:
    std::unique_ptr<b2Body> createBody(const b2BodyDef &bd, MyWorld &world) const override;

public:
    Object2D(MyWorld &world, ObjectType type);
    Object2D(MyWorld &world, ObjectType type, b2Vec2 position, float angle);
};

#endif