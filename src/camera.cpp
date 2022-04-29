#include "camera.h"
#include "enemy.h"  // Circular dependency

inline float Camera::getDimFactor(const MyCallback &callback)
{
    // float dimFactor = 1.0f / callback.getFraction() * vecCosine(callback.normal_, callback.ray_) / 20;
    float dimFactor = (vecCosine(callback.normal_, callback.ray_) * 0.75f + (1.0f / 2.2f)) / 20 * (-callback.getFraction() * rayLength_ / 100 + 1.3f) * 10;
    // std::cerr << dimFactor << '\n'; // DEBUG
    return dimFactor;
    // return 0.4f / callback.getFraction() * vecCosine(callback.normal_, callback.ray_);
}

inline Camera::scale_t Camera::get3DScale(float adjacentDistance)
{
    return {
        (adjacentDistance + 756.52173f) * 0.8827916f / raysNumber_,
        100.0f / adjacentDistance};
}

inline Camera::scale_t Camera::get2DScale(float adjacentDistance)
{
    return {
        28.0f / adjacentDistance / FOVMaxAngle_,
        56.0f / adjacentDistance};
}

// #include "timer.h" // DEBUG

void Camera::drawRay(UserIO &userIO, float angle, const MyCallback &callback)
{
    // static Timer t; // DEBUG
    // t.start();      // DEBUG

    // y component of distance measured in local coordinate system
    float adjacentDistance{cos(angle) * callback.getFraction() * rayLength_};
    scale_t scale{get3DScale(adjacentDistance)};

    float dimFactor = getDimFactor(callback);

    static const float maxCordX{tan(FOVMaxAngle_)};
    userIO.drawOnScreen(callback.getShapeIdx(), tan(angle) / maxCordX, 0.0f, scale.first, scale.second, dimFactor);

    // t.stop(); // DEBUG
}

void Camera::drawRay(UserIO &userIO, float angle, const MyCallback &callback, float distance)
{
    // y component of distance measured in local coordinate system
    float adjacentDistance{cos(angle) * callback.getFraction() * distance};
    scale_t scale{get2DScale(adjacentDistance)};

    static const float maxCordX{tan(FOVMaxAngle_)};
    userIO.drawOnScreen(callback.getShapeIdx(), tan(angle) / maxCordX, 0.0f, scale.first, scale.second);
}

Camera::MyCallback Camera::sendRay(const b2World &world, const b2Vec2 &cameraPosition, const b2Vec2 &ray)
{
    MyCallback rayCallback;

    // Changing direction of vector in callback
    rayCallback.ray_ = -ray;

    // Casting a Box2D ray
    world.RayCast(&rayCallback, cameraPosition, cameraPosition + ray);
    return rayCallback;
}

Camera::MyCallback Camera::sendRay(const b2World &world, const b2Vec2 &cameraPosition, float angle, float length)
{
    // Calculate ray
    b2Vec2 ray{getVector(angle)};
    ray.Normalize();
    ray *= length;

    // Send ray in a given direction
    return sendRay(world, cameraPosition, ray);
}

bool Camera::ifInFieldOfView(const Object &camera, const Object &object)
{
    // Create view vector
    b2Vec2 viewVector{getVector(camera.getAngle())};

    // Create vector to given object
    b2Vec2 objectVector{getVector(camera.getPosition(), object.getPosition())};

    // Check if the angle between the two vectors is less than FOVMaxAngle
    float angle{vecAngle(viewVector, objectVector)};
    // std::cerr << angle << '\n';
    return angle < FOVMaxAngle_;
}

void Camera::drawViewOnScreen(UserIO &userIO, const MyWorld &world, const Object &camera, const Enemy &enemy)
{
    userIO.start(); // Start frame drawing

    // Angle between casted rays
    constexpr float angleChange{2.0f * FOVMaxAngle_ / raysNumber_};

    // Cast a rays in many directions
    // for drawing Object3Ds
    for (float angle{-FOVMaxAngle_}; angle <= FOVMaxAngle_; angle += angleChange)
    {
        // Rays can only hit Object3Ds
        MyCallback rayCallback = sendRay(world, camera.getPosition(), angle + camera.getAngle());

        if (rayCallback.hit())
            drawRay(userIO, angle, rayCallback);
    }

    // Drawing Object2D
    // For each one check if it is in current fieldOfView
    if (enemy.spawned() && ifInFieldOfView(camera, enemy))
    {
        // If enemy is in the field of view
        // send a ray in the enemy's this direction
        b2Vec2 ray{getVector(camera.getPosition(), enemy.getPosition())};
        MyCallback rayCallback = sendRay(world, camera.getPosition(), ray);

        if (!rayCallback.hit())
        {
            // If none object3D block enemy's view
            // draw it
            rayCallback.shapeIdx_ = enemy.getShapeIdx();
            float objectAngle{vecAngle(getVector(camera.getAngle()), ray)};

            // Differenciate when the object's on the left side
            // from when it's on the right side
            float cross = b2Cross(getVector(camera.getAngle()), ray);
            objectAngle *= abs(cross) / cross;

            drawRay(userIO, objectAngle, rayCallback, b2Distance(getVector(camera.getAngle()), ray));
        }
    }

    userIO.end();   // Display ray on screen
}

float Camera::MyCallback::ReportFixture(b2Fixture *fixture, const b2Vec2 &point, const b2Vec2 &normal, float fraction)
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
