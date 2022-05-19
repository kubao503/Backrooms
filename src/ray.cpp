#include "ray.h"

inline void Ray::sendRay(RayCallback &callback, const b2World &world, const b2Vec2 &cameraPosition, const b2Vec2 &ray)
{
    // Changing direction of vector in callback
    callback.ray_ = -ray;

    // Casting a Box2D ray
    world.RayCast(&callback, cameraPosition, cameraPosition + ray);
}

void Ray::sendRay(RayCallback &callback, const b2World &world, const b2Vec2 &cameraPosition, float angle, float length)
{
    // Calculate ray
    b2Vec2 ray{getVec(angle)};
    ray.Normalize();
    ray *= length;

    // Send ray in a given direction
    sendRay(callback, world, cameraPosition, ray);
}

float Ray::RayCallback::ReportFixture(b2Fixture *fixture, const b2Vec2 &point, const b2Vec2 &normal, float fraction)
{
    // Non-zero userData pointer means that's Object3D
    const Object3D *obj = (Object3D *)fixture->GetUserData().pointer;
    if (!obj)
        return -1.0f; // Continue ray travel

    // Gather information about hit
    object_ = obj;
    hitPoint_ = point;
    shapeIdx_ = obj->getShapeIdx();
    normal_ = normal;
    return fraction_ = fraction; // Stop ray at current position
}
