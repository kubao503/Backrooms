#ifndef RAY_394_H
#define RAY_394_H

#include "shapes.h"      // for Shape manipulation
#include "myMath.h"      // for vector calculations
#include "object3d.h"    // for casting hit object to Object3D
#include <box2d/box2d.h> // for raycast

class Ray
{
public:
    // Class used to get feedback from ray-fixture collisions
    class RayCallback : public b2RayCastCallback
    {
        friend class Ray;

        float fraction_{maxFraction}; // The measured distance
        Shapes::Type shapeIdx_{Shapes::TOTAL};
        b2Vec2 normal_{0.0f, 0.0f};
        b2Vec2 ray_{0.0f, 0.0f};
        b2Vec2 hitPoint_{0.0f, 0.0f};
        Object *object_;
        float ReportFixture(b2Fixture *fixture, const b2Vec2 &point, const b2Vec2 &normal, float fraction) override;

    public:
        float getFraction() const { return fraction_; }
        Shapes::Type getShapeIdx() const { return shapeIdx_; }
        b2Vec2 getNormal() const { return normal_; }
        b2Vec2 getRay() const { return ray_; }
        Object *getObject() const { return object_; }
        const b2Vec2 &getHitPoint() const { return hitPoint_; }

        bool hit() const { return fraction_ < maxFraction; }
        void setShapeIdx(Shapes::Type type) { shapeIdx_ = type; }
    };

    static RayCallback sendRay(const b2World &world, const b2Vec2 &cameraPosition, float angle, float length);
    static RayCallback sendRay(const b2World &world, const b2Vec2 &cameraPosition, const b2Vec2 &ray);

private:
    static constexpr float maxFraction{1.0f};
};

#endif
