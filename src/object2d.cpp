#include "object2d.h"

Object2D::Object2D(b2World &world, Type type, const b2Vec2 &position, float angle)
    : DrawableObject{world, type, position, angle} {}
