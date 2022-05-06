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

// Returns the vector between given points
inline b2Vec2 getVec(const b2Vec2 &point1, const b2Vec2 &point2)
{
    return point2 - point1;
}

// Returned vecotor is not normalized!
// The length can vary
inline b2Vec2 getVec(float angle)
{
    return b2Vec2(cos(angle), sin(angle));
}

// Normalized version of getVec(float)
inline b2Vec2 getVecN(float angle)
{
    b2Vec2 temp = getVec(angle);
    temp.Normalize();
    return temp;
}

inline float distance(const b2Vec2 &pos1, const b2Vec2 &pos2)
{
    return (pos1 - pos2).Length();
}

inline b2Vec2 rotateVec(const b2Vec2 &vec, float angle)
{
    return {
        vec.x * sin(angle) + vec.y * cos(angle),
        -vec.x * cos(angle) + vec.y * sin(angle)};
}

inline int modulo(int value, int mod)
{
    return ((value % mod) + mod) % mod;
}

#endif
