#ifndef CAMERA_H
#define CAMERA_H

#include "userio.h"
#include "shapes.h"
#include "myWorld.h"

#include <box2d/box2d.h>

extern UserIO userio_g;
// extern b2World world_g;

class Camera
{
private:
    // static float getRayHit(const b2RayCastInput &input);

    // Draws an object hit by a ray
    static void drawRay(float angle, float distance);

    class MyCallback : public b2RayCastCallback
    {
        float fraction_{1.0f};
        float ReportFixture(b2Fixture *fixture, const b2Vec2 &point, const b2Vec2 &normal, float fraction) override;

    public:
        MyCallback(float maxFraction) : fraction_{maxFraction} {}
        float getFraction() { return fraction_; }
    };

public:
    static void raycast(const MyWorld &world, const b2Vec2 &cameraPosition, float defaultAngle);
};

#endif