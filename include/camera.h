#ifndef CAMERA_H
#define CAMERA_H

#include "userio.h"    // called to draw Shape on screen
#include "shapes.h"    // for Shape manipulation
#include "myWorld.h"   // needed by UserIO to draw ray hit
#include "constants.h" // for PI needed in angle calculations
#include "object3d.h"  // for drawing Object3D
#include "object2d.h"  // for drawing Object2D

#include <box2d/box2d.h> // for raycast

// DEBUG
// #include <iostream>

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

    using scale_t = std::pair<float, float>;

    static constexpr float maxFraction_{1.0f};
    static constexpr float FOVMaxAngle_{PI / 5.0f};
    static constexpr int raysNumber_{404};
    static constexpr float rayLength_{100.0f};

    // Draws texture at ray's hitpoint
    static float getDimFactor(const MyCallback &callback);
    static scale_t get3DScale(float adjacentDistance);
    static scale_t get2DScale(float adjacentDistance);

    // For 3D objects
    static void drawRay(UserIO &userIO, float angle, const MyCallback &callback);
    // For 2D objects
    static void drawRay(UserIO &userIO, float angle, const MyCallback &callback, float distance);

    static void sendRay(const MyWorld &world, MyCallback &rayCallback, const b2Vec2 &cameraPosition, float angle);
    static void sendRay(const MyWorld &world, MyCallback &rayCallback, const b2Vec2 &cameraPosition, const b2Vec2 &ray);
    static bool ifInFieldOfView(const Object &camera, const Object &object);

public:
    // Casts multiple rays to show them as image on the screen
    static void drawViewOnScreen(UserIO &userIO, const MyWorld &world, const Object &camera, const Object2D &object2D);
};

// Math
inline float vecCosine(const b2Vec2 &vec1, const b2Vec2 &vec2);
inline float vecAngle(const b2Vec2 &vec1, const b2Vec2 &vec2);
inline b2Vec2 getVector(const b2Vec2 &point1, const b2Vec2 &point2);
inline b2Vec2 getVector(float angle);

#endif
