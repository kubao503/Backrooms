#ifndef CAMERA_H
#define CAMERA_H

#include "userio.h"         // called to draw Shape on screen
#include "shapes.h"         // for Shape manipulation
#include "myWorld.h"        // needed by UserIO to draw ray hit
#include "constants.h"      // for PI needed in angle calculations
#include "object3d.h"       // for getting shapeIdx_ from Object3D

#include <box2d/box2d.h>    // for raycast

class Camera
{
private:
    // Class used to get feedback from ray-fixture collisions
    class MyCallback : public b2RayCastCallback
    {
        friend class Camera;

        float fraction_{maxFraction_}; // The measured distance
        Shapes::Type shapeIdx_{Shapes::TOTAL};
        b2Vec2 normal_{0.0f, 0.0f};
        b2Vec2 ray_{0.0f, 0.0f};
        float ReportFixture(b2Fixture *fixture, const b2Vec2 &point, const b2Vec2 &normal, float fraction) override;

    public:
        float getFraction() const { return fraction_; }
        Shapes::Type getShapeIdx() const { return shapeIdx_; }
    };

    // Draws texture at ray's hitpoint
    static void drawRay(UserIO &userIO, float angle, const MyCallback &callback);
    static void sendRay(const MyWorld &world, MyCallback &rayCallback, const b2Vec2 &cameraPosition, float angle, float defaultAngle);

    static constexpr float maxFraction_{1.0f};
    static constexpr float FOVMaxAngle_{PI / 6.0f};
    static constexpr int raysNumber_{104};
    static constexpr float renderDistance_{300.0f};

public:
    // Casts multiple rays to show them as image on the screen
    static void drawViewOnScreen(UserIO &userIO, const MyWorld &world, const b2Vec2 &cameraPosition, float defaultAngle);
};

#endif