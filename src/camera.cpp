#include "camera.h"

inline float Camera::getDimFactor(const Ray::RayCallback &callback)
{
    // float dimFactor = 1.0f / callback.getFraction() * vecCosine(callback.normal_, callback.ray_) / 20;
    float dimFactor = (vecCosine(callback.getNormal(), callback.getRay()) * 0.375f + 0.454545f) * (-callback.getFraction() * Conf::renderDistance / 100.0f + 1.3f);
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
        8.0f / adjacentDistance / Conf::FOVangle,
        10.0f / adjacentDistance};
}

void Camera::draw3DRay(UserIO &userIO, float angle, const Ray::RayCallback &callback, float rayNumber)
{
    // y component of distance measured in local coordinate system
    float adjacentDistance{cos(angle) * callback.getFraction() * Conf::renderDistance};
    scale_t scale{get3DScale(adjacentDistance)};

    float dimFactor = getDimFactor(callback);

    static const float maxCordX{tan(Conf::FOVangle / 2.0f)};

    userIO.drawOnScreen(callback.getShapeIdx(), tan(angle) / maxCordX, 0.0f, scale.first, scale.second, dimFactor, rayNumber);
}

void Camera::draw2DRay(UserIO &userIO, float angle, const Ray::RayCallback &callback, float distance)
{
    // y component of distance measured in local coordinate system
    float adjacentDistance{cos(angle) * callback.getFraction() * distance};
    scale_t scale{get2DScale(adjacentDistance)};

    static const float maxCordX{tan(Conf::FOVangle / 2.0f)};
    userIO.drawOnScreen(callback.getShapeIdx(), tan(angle) / maxCordX, 0.0f, scale.first, scale.second);
}

bool Camera::ifInFieldOfView(const Object &camera, const Object &object)
{
    // Create view vector
    b2Vec2 viewVector{getVec(camera.getAngle())};

    // Create vector to given object
    b2Vec2 objectVector{getVec(camera.getPosition(), object.getPosition())};

    // Check if the angle between the two vectors is less than FOVMaxAngle
    float angle{vecAngle(viewVector, objectVector)};
    return angle < Conf::FOVangle / 2.0f;
}

void Camera::drawObjects3D(UserIO &userIO, const Player &player)
{
    // Angle between casted rays
    constexpr float angleChange{Conf::FOVangle / raysNumber_};
    Object *lastObject{nullptr}; // Last drawn object
    b2Vec2 closestCorner;        // Corner of this object

    // Cast a rays in many directions
    // for drawing Object3Ds
    for (float angle{-Conf::FOVangle / 2.0f}; angle <= Conf::FOVangle / 2.0f; angle += angleChange)
    {
        // Rays can only hit Object3Ds
        Ray::RayCallback rayCallback = Ray::sendRay(player.getWorld(), player.getPosition(), angle + player.getAngle(), Conf::renderDistance);

        if (rayCallback.hit())
        {
            if (lastObject != rayCallback.getObject())
            {
                // Start drawing texture from begining
                lastObject = rayCallback.getObject();
                closestCorner = static_cast<Object3D *>(rayCallback.getObject())->getClosestCorner(player.getPosition());
            }

            float rayNumber{distance(rayCallback.getHitPoint(), closestCorner)};
            draw3DRay(userIO, angle, rayCallback, rayNumber);
        }
    }
}

void Camera::drawObjects2D(UserIO &userIO, const Player &player)
{
    for (auto object2D : player.getVisibleObjects())
    {
        // Drawing Object2D
        // Send a ray in the object2D's this direction
        b2Vec2 ray{getVec(player.getPosition(), object2D->getPosition())};
        Ray::RayCallback rayCallback = Ray::sendRay(player.getWorld(), player.getPosition(), ray);

        if (!rayCallback.hit())
        {
            // If none object3D block object2D's view
            // draw it
            rayCallback.setShapeIdx(object2D->getShapeIdx());
            float objectAngle{vecAngle(getVec(player.getAngle()), ray)};

            // Differenciate when the object's on the left side
            // from when it's on the right side
            float cross = b2Cross(getVec(player.getAngle()), ray);
            objectAngle *= abs(cross) / cross;

            draw2DRay(userIO, objectAngle, rayCallback, b2Distance(getVec(player.getAngle()), ray));
        }
    }
}

void Camera::drawItems(UserIO &userIO, const Player &player)
{
    if (player.getOwnedItems().size())
        userIO.drawOnScreen(Shapes::RED_WALL);
}

void Camera::drawViewOnScreen(UserIO &userIO, const Player &player)
{
    userIO.start(); // Start frame drawing

    drawObjects3D(userIO, player);
    drawObjects2D(userIO, player);
    drawItems(userIO, player);

    userIO.end(); // Display ray on screen
}
