#ifndef MATH_1293453_H
#define MATH_1293453_H

#include <box2d/box2d.h> // for vector calculations
#include <cmath>

constexpr float PI{static_cast<float>(M_PI)};

// Math
inline float vecCosine(const b2Vec2 &vec1, const b2Vec2 &vec2)
{
    return b2Dot(vec1, vec2) / vec1.Length() / vec2.Length();
}

inline float vecAngle(const b2Vec2 &vec1, const b2Vec2 &vec2)
{
    return acos(vecCosine(vec1, vec2));
}

inline b2Vec2 getVector(const b2Vec2 &point1, const b2Vec2 &point2)
{
    return b2Vec2(point2.x - point1.x, point2.y - point1.y);
}

inline b2Vec2 getVector(float angle)
{
    return b2Vec2(cos(angle), sin(angle));
}

#endif
