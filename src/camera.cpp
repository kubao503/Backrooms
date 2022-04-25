#include "camera.h"

void Camera::drawRay(UserIO &userIO, float angle, const MyCallback &callback)
{
    // Draw texture at the closest hit point
    float adjacentDistance{cos(angle) * callback.getFraction()};

    float xScale{(2.3f * adjacentDistance + 5.8f) * 198.625f * FOVMaxAngle_ / raysNumber_};
    float yScale{3.0f / adjacentDistance};

    float dotProduct{b2Dot(callback.normal_, callback.ray_)};
    float vecCosine{dotProduct / callback.normal_.Length() / callback.ray_.Length()};
    float dimFactor{0.4f / callback.getFraction() * (0.5f * vecCosine + 0.5f)};
    userIO.drawOnScreen(callback.getShapeIdx(), tan(angle) * 1000.0f, 0.0f, xScale, yScale, dimFactor);
}

void Camera::sendRay(const MyWorld &world, MyCallback &rayCallback, const b2Vec2 &cameraPosition, float angle, float defaultAngle)
{
    // Create calculate ray vector
    b2Vec2 begin{cameraPosition};
    b2Vec2 ray{cos(angle + defaultAngle) * renderDistance_, sin(angle + defaultAngle) * renderDistance_};
    rayCallback.ray_ = -ray;

    // Send ray in a given direction
    world.RayCast(&rayCallback, begin, begin + ray);
}

void Camera::drawViewOnScreen(UserIO &userIO, const MyWorld &world, const b2Vec2 &cameraPosition, float defaultAngle)
{
    userIO.start();

    constexpr float angleChange{2.0f * FOVMaxAngle_ / raysNumber_};

    // Cast a rays in many directions
    for (float angle{-FOVMaxAngle_}; angle <= FOVMaxAngle_; angle += angleChange)
    {
        MyCallback rayCallback;

        sendRay(world, rayCallback, cameraPosition, angle, defaultAngle);

        // Draw if the ray went shorter than max distance
        if (rayCallback.getFraction() < maxFraction_)
            drawRay(userIO, angle, rayCallback);
    }

    userIO.end();
}

float Camera::MyCallback::ReportFixture(b2Fixture *fixture, const b2Vec2 &point, const b2Vec2 &normal, float fraction)
{
    MyBody* ptr = dynamic_cast<MyBody *>(fixture->GetBody());
    if (!ptr)
        return 1.0f;
    shapeIdx_ = ptr->getObject().getShapeIdx();
    normal_ = normal;
    return fraction_ = fraction;
    (void)point;    // For -Werror=unused-variable
}