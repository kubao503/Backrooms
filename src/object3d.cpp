#include "object3d.h"

Object3D::Object3D(b2World &world, ObjectType type)
    : Object{world, type}
{
    // Setting Object3D as user data
    body_->GetUserData().pointer = (uintptr_t)this;
}

Object3D::Object3D(b2World &world, ObjectType type, b2Vec2 position, float angle)
    : Object{world, type, position, angle}
{
    // Setting Object3D as user data
    body_->GetUserData().pointer = (uintptr_t)this;
}
