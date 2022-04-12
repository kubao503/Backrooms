#include "camera.h"

void Camera::drawRay(UserIO &userio, float angle, const MyCallback &callback)
{
    // Draw texture at the closest hit point
    float adjacentDistance{cos(angle) * callback.getFraction()};
    float xScale{(2.3f * adjacentDistance + 5.8f) * 198.625f * FOVMaxAngle_ / raysNumber_};
    float yScale{3.0f / adjacentDistance};
    userio.drawOnScreen(callback.getShapeIdx(), tan(angle) * 1000.0f, 0.0f, xScale, yScale);
}

void Camera::raycast(UserIO &userio, const MyWorld &world, const b2Vec2 &cameraPosition, float defaultAngle)
{
    constexpr float rayLength{300.0f};
    constexpr float angleChange{2.0f * FOVMaxAngle_ / raysNumber_};

    // Cast a rays in many directions
    for (float angle{-FOVMaxAngle_}; angle <= FOVMaxAngle_; angle += angleChange)
    {
        // Create calculate ray vector
        b2Vec2 p1{cameraPosition}, p2{cameraPosition};
        p2 += b2Vec2(cos(angle + defaultAngle) * rayLength, sin(angle + defaultAngle) * rayLength);

        // Send ray in given direction
        MyCallback rayCallback;
        world.RayCast(&rayCallback, p1, p2);

        // Check if the ray went shorter than max distance
        if (rayCallback.getFraction() < maxFraction_)
        {
            drawRay(userio, angle, rayCallback);
        }
    }
}

float Camera::MyCallback::ReportFixture(b2Fixture *fixture, const b2Vec2 &point, const b2Vec2 &normal, float fraction)
{
    shapeIdx_ = static_cast<MyBody *>(fixture->GetBody())->getObject().getShapeIdx();
    return fraction_ = fraction;
    (void)point;
    (void)normal;
}