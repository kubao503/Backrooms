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
    b2Vec2 ray{getVector(angle)};
    ray.Normalize();
    ray *= length;

    // Send ray in a given direction
    return sendRay(world, cameraPosition, ray);
}

float Ray::RayCallback::ReportFixture(b2Fixture *fixture, const b2Vec2 &point, const b2Vec2 &normal, float fraction)
{
    // Successful cast to MyBody means that's Object3D
    MyBody *ptr = dynamic_cast<MyBody *>(fixture->GetBody());
    if (!ptr)
        return 1.0f;             // Continue ray travel

    // Gather information about hit
    shapeIdx_ = ptr->getObject().getShapeIdx();
    normal_ = normal;
    return fraction_ = fraction; // Stop ray at current position
    (void)point; // For -Werror=unused-variable
}
