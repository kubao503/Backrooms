#include "object3d.h"

b2Vec2 *Object3D::getCorners() const
{
    return dynamic_cast<b2PolygonShape *>(body_->GetFixtureList()[0].GetShape())->m_vertices;
}

b2Vec2 Object3D::getClosestCorner(const b2Vec2 &playerPos) const
{
    constexpr int cornersNumber{4};
    b2Vec2 *vertices{getCorners()};

    b2Vec2 closestCorner;
    float smallestDist{std::numeric_limits<float>::infinity()};

    // Checking distance between all corners
    for (int i{0}; i < cornersNumber; ++i)
    {
        b2Vec2 corner = rotateVec(vertices[i], getAngle() + PI / 2.0f) + getPosition();

        if (distance(corner, playerPos) < smallestDist)
        {
            closestCorner = corner;
            smallestDist = distance(corner, playerPos);
        }
    }

    return closestCorner;
}

Object3D::Object3D(b2World &world, ObjectType type)
    : Object{world, type}
{
    // Setting Object3D as user data
    body_->GetUserData().pointer = (uintptr_t)this;
}

Object3D::Object3D(b2World &world, ObjectType type, const b2Vec2 &position, float angle)
    : Object{world, type, position, angle}
{
    // Setting Object3D as user data
    body_->GetUserData().pointer = (uintptr_t)this;
}
