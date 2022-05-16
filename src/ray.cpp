#include "ray.h"

Ray::RayCallback Ray::sendRay(const b2World &world, const b2Vec2 &cameraPosition, const b2Vec2 &ray)
{
    RayCallback rayCallback;

    // Changing direction of vector in callback
    rayCallback.ray_ = -ray;

    // Casting a Box2D ray
    world.RayCast(&rayCallback, cameraPosition, cameraPosition + ray);
    return rayCallback;
}

Ray::RayCallback Ray::sendRay(const b2World &world, const b2Vec2 &cameraPosition, float angle, float length)
{
    // Calculate ray
    b2Vec2 ray{getVec(angle)};
    ray.Normalize();
    ray *= length;

    // Send ray in a given direction
    return sendRay(world, cameraPosition, ray);
}

float Ray::RayCallback::ReportFixture(b2Fixture *fixture, const b2Vec2 &point, const b2Vec2 &normal, float fraction)
{
    // Non-zero userData pointer means that's Object3D
    Object *userData = (Object *)fixture->GetBody()->GetUserData().pointer;
    Object3D *obj = dynamic_cast<Object3D *>(userData);
    if (!obj)
        return -1.0f; // Continue ray travel

    // Gather information about hit
    object_ = obj;
    hitPoint_ = point;
    shapeIdx_ = obj->getShapeIdx();
    normal_ = normal;
    return fraction_ = fraction; // Stop ray at current position
}
