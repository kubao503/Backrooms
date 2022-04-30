#include "object2d.h"

Object2D::Object2D(b2World &world, ObjectType type)
    : Object{world, type} {}

Object2D::Object2D(b2World &world, ObjectType type, b2Vec2 position, float angle)
    : Object{world, type, position, angle} {}
