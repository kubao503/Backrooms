#ifndef CAMERA_H
#define CAMERA_H

#include "userio.h"
#include "shapes.h"
#include "myWorld.h"
#include "constants.h"

#include <box2d/box2d.h>

class Camera
{
private:
    // Class used to get feedback from ray-fixture collisions
    class MyCallback : public b2RayCastCallback
    {
        float fraction_{maxFraction_};
        Shapes::Type shapeIdx_{Shapes::TOTAL};
        float ReportFixture(b2Fixture *fixture, const b2Vec2 &point, const b2Vec2 &normal, float fraction) override;

    public:
        float getFraction() const { return fraction_; }
        Shapes::Type getShapeIdx() const { return shapeIdx_; }
    };

    // Draws texture at ray's hitpoint
    static void drawRay(UserIO &userio, float angle, const MyCallback &callback);
    static void sendRay(const MyWorld &world, MyCallback &rayCallback, const b2Vec2 &cameraPosition, float angle, float defaultAngle);

    static constexpr float maxFraction_{1.0f};
    static constexpr float FOVMaxAngle_{PI / 6.0f};
    static constexpr int raysNumber_{104};
    static constexpr float renderDistance{300.0f};

public:
    // Casts multiple rays to show them as image on the screen
    static void drawViewOnScreen(UserIO &userio, const MyWorld &world, const b2Vec2 &cameraPosition, float defaultAngle);
};

#endif