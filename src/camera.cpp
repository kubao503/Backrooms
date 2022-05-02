#include "camera.h"

inline float Camera::getDimFactor(const Ray::RayCallback &callback)
{
    // float dimFactor = 1.0f / callback.getFraction() * vecCosine(callback.normal_, callback.ray_) / 20;
    float dimFactor = (vecCosine(callback.getNormal(), callback.getRay()) * 0.375f + 0.454545f) * (-callback.getFraction() * renderDistance_ / 100.0f + 1.3f);
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

void Camera::drawRay(UserIO &userIO, float angle, const Ray::RayCallback &callback)
{
    // y component of distance measured in local coordinate system
    float adjacentDistance{cos(angle) * callback.getFraction() * renderDistance_};
    scale_t scale{get3DScale(adjacentDistance)};

    float dimFactor = getDimFactor(callback);

    static const float maxCordX{tan(FOVMaxAngle_)};
    userIO.drawOnScreen(callback.getShapeIdx(), tan(angle) / maxCordX, 0.0f, scale.first, scale.second, dimFactor);
}

void Camera::drawRay(UserIO &userIO, float angle, const Ray::RayCallback &callback, float distance)
{
    // y component of distance measured in local coordinate system
    float adjacentDistance{cos(angle) * callback.getFraction() * distance};
    scale_t scale{get2DScale(adjacentDistance)};

    static const float maxCordX{tan(FOVMaxAngle_)};
    userIO.drawOnScreen(callback.getShapeIdx(), tan(angle) / maxCordX, 0.0f, scale.first, scale.second);
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

void Camera::drawViewOnScreen(UserIO &userIO, const b2World &world, const Object &camera, const std::vector<Object2D> &object2Ds)
{
    userIO.start(); // Start frame drawing

    // Angle between casted rays
    constexpr float angleChange{2.0f * FOVMaxAngle_ / raysNumber_};

    // Cast a rays in many directions
    // for drawing Object3Ds
    for (float angle{-FOVMaxAngle_}; angle <= FOVMaxAngle_; angle += angleChange)
    {
        // Rays can only hit Object3Ds
        Ray::RayCallback rayCallback = Ray::sendRay(world, camera.getPosition(), angle + camera.getAngle(), renderDistance_);

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
        Ray::RayCallback rayCallback = Ray::sendRay(world, camera.getPosition(), ray);

        if (!rayCallback.hit())
        {
            // If none object3D block enemy's view
            // draw it
            rayCallback.setShapeIdx(enemy.getShapeIdx());
            float objectAngle{vecAngle(getVector(camera.getAngle()), ray)};

            // Differenciate when the object's on the left side
            // from when it's on the right side
            float cross = b2Cross(getVector(camera.getAngle()), ray);
            objectAngle *= abs(cross) / cross;

            drawRay(userIO, objectAngle, rayCallback, b2Distance(getVector(camera.getAngle()), ray));
        }
    }

    userIO.end(); // Display ray on screen
}
