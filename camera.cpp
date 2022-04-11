#include "camera.h"

void Camera::drawRay(float angle, float distance)
{
    // Draw the closest hit point
    float adjacentDistance{cos(angle) * distance};
    float xScale{2.3f * adjacentDistance + 5.8f};
    float yScale{3.0f / adjacentDistance};
    userio_g.drawOnScreen(Shapes::WALL, tan(angle) * 1000.0f, 0.0f, xScale, yScale);
}

float Camera::getRayHit(const b2RayCastInput &input)
{
    float smallestFraction{input.maxFraction};

    // iterate over all bodies and raycast them
    for (b2Body *b = world_g.GetBodyList(); b; b = b->GetNext())
    {
        b2RayCastOutput output;
        b2Fixture *fixList{b->GetFixtureList()};
        bool hit{fixList[0].RayCast(&output, input, 0)};

        // if a body is hit, check if this is the closest hit
        if (hit && output.fraction < smallestFraction)
        {
            smallestFraction = output.fraction;
        }
    }

    return smallestFraction;
}

void Camera::raycast(const b2Vec2 &cameraPosition, float defaultAngle)
{
    const float rayLength{300.0f};
    const float FOVMaxAngle{M_PI / 6.0f};

    // Cast a ray in any direction
    for (float angle{-FOVMaxAngle}; angle <= FOVMaxAngle; angle += 0.01f)
    {
        b2RayCastInput input;
        input.p1 = input.p2 = cameraPosition;
        input.p2 += b2Vec2(cos(angle + defaultAngle) * rayLength, sin(angle + defaultAngle) * rayLength);

        MyCallback callback(input.maxFraction = 1.0);
        world_g.RayCast(&callback, input.p1, input.p2);

        // float smallestFraction{getRayHit(input)};
        float smallestFraction{callback.getFraction()};

        // Calculate the closes hit point
        b2Vec2 hitPoint{input.p1 + smallestFraction * (input.p2 - input.p1)};

        if (smallestFraction < input.maxFraction)
        {
            drawRay(angle, smallestFraction);
        }
    }
}

float Camera::MyCallback::ReportFixture(b2Fixture *fixture, const b2Vec2 &point, const b2Vec2 &normal, float fraction)
{
    return fraction_ = fraction;
}