#include "object3d.h"

b2Vec2 *Object3D::getCorners() const
{
    return dynamic_cast<b2PolygonShape *>(body_->GetFixtureList()[0].GetShape())->m_vertices;
}

std::pair<b2Vec2, b2Vec2> Object3D::getClosestCorner(const b2Vec2 &playerPos) const
{
    constexpr int cornersNumber{4};
    const b2Vec2 *vertices{getCorners()};
    b2Vec2 corners[cornersNumber];

    int closestCornerIdx;
    float smallestDist{std::numeric_limits<float>::infinity()};

    // Checking distance between all corners
    for (int i{0}; i < cornersNumber; ++i)
    {
        // Transform from local to global coordinates
        corners[i] = rotateVec(vertices[i], getAngle() + PI / 2.0f) + getPosition();

        if (distance(corners[i], playerPos) < smallestDist)
        {
            closestCornerIdx = i;
            smallestDist = distance(corners[i], playerPos);
        }
    }

    int leftCornerIdx{modulo(closestCornerIdx - 1, cornersNumber)};
    return {corners[leftCornerIdx], corners[closestCornerIdx]};
}

Object3D::Object3D(b2World &world, Type type, const b2Vec2 &position, float angle)
    : DrawableObject{world, type, position, angle}
{
    setCollisionFilter(WALL);
}
