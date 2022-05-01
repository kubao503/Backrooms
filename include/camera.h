#ifndef CAMERA_H
#define CAMERA_H

#include "userio.h"   // called to draw Shape on screen
#include "object2d.h" // for drawing Object2D
#include "myMath.h"   // for angle calculations
#include "enemy.h"    // for drawing Enemy
#include "ray.h"      // for casting rays

class Camera
{
private:
    using scale_t = std::pair<float, float>;

    static constexpr float FOVMaxAngle_{PI / 5.0f};
    static constexpr float renderDistance_{100.0f};
    static constexpr int raysNumber_{50};

    // Draws texture at ray's hitpoint
    static float getDimFactor(const Ray::RayCallback &callback);
    static scale_t get3DScale(float adjacentDistance);
    static scale_t get2DScale(float adjacentDistance);

    // For 3D objects
    static void drawRay(UserIO &userIO, float angle, const Ray::RayCallback &callback);
    // For 2D objects
    static void drawRay(UserIO &userIO, float angle, const Ray::RayCallback &callback, float distance);

    static bool ifInFieldOfView(const Object &camera, const Object &object);

public:
    // Casts multiple rays to show them as image on the screen
    static void drawViewOnScreen(UserIO &userIO, const b2World &world, const Object &camera, const Enemy &enemy);
};

#endif
