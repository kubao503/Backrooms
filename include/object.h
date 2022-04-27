#ifndef OBJECT_H
#define OBJECT_H

#include "shapes.h"  // for shapeIdx_ attribute
#include "myWorld.h" // needed for creating b2Body

#include <memory>     // for b2Body smart pointer
#include <functional> // for storing fixture calls

// DEBUG
// #include <iostream>

class Object
{
public:
    enum ObjectType
    {
        WALL,
        WALL2,
        PLAYER,
        ENEMY,
        TOTAL
    };

protected:
    enum class BodyType
    {
        STATIC,
        DYNAMIC
    };

    const Shapes::Type shapeIdx_;
    std::unique_ptr<b2Body> body_{nullptr};

    // Returns unique position helping avoiding spawning
    // objects at the same place
    b2Vec2 getNewPosition() const;
    static const b2BodyDef &getBodyDef(BodyType bodyType);
    static const b2FixtureDef *getFixtureDef(const b2Vec2 &size);
    static const b2FixtureDef *getFixtureDef(float radius);

    virtual std::unique_ptr<b2Body> createBody(const b2BodyDef &bd, MyWorld &world) const = 0;
    virtual ~Object() = default;

    Object(ObjectType objectType);
    // Object(MyWorld &world, Shapes::Type shapeIdx, BodyType bodyType, const b2Vec2 &size);
    void setBody(MyWorld &world, ObjectType type);
    void setBody(MyWorld &world, ObjectType type, b2Vec2 position, float angle);

    static const std::function<const b2FixtureDef *()> fixtureCalls[ObjectType::TOTAL];
    const static constexpr Shapes::Type shapeIdx[ObjectType::TOTAL]{
        Shapes::WALL, Shapes::RED_WALL, Shapes::PLAYER, Shapes::ENEMY};

    static constexpr BodyType bodyTypes[ObjectType::TOTAL]{
        BodyType::STATIC, BodyType::STATIC, BodyType::DYNAMIC, BodyType::STATIC};

public:
    Object(MyWorld &world, ObjectType objectType);
    Shapes::Type getShapeIdx() const { return shapeIdx_; }
    const b2Vec2 &getPosition() const { return body_->GetPosition(); };
    float getAngle() const { return body_->GetAngle(); };
};

#endif