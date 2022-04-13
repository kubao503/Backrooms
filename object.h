#ifndef OBJECT_H
#define OBJECT_H

#include "shapes.h"
#include "myWorld.h"

#include <box2d/box2d.h>
#include <memory>

class Object
{
public:
    enum ObjectType
    {
        WALL,
        WALL2,
        PLAYER,
        TOTAL
    };

protected:
    enum class BodyType
    {
        STATIC,
        DYNAMIC
    };

    const Shapes::Type shapeIdx_;
    std::unique_ptr<MyBody> body_{nullptr};

    // Returns unique position helping avoiding spawning
    // objects at the same place
    b2Vec2 getNewPosition() const;
    const b2BodyDef &getBodyDef(BodyType bodyType);
    const b2FixtureDef &getFixtureDef(const b2Vec2 &size);

    Object(MyWorld &world, Shapes::Type shapeIdx, const b2BodyDef &bodyDef, const b2FixtureDef &fixture);
    Object(MyWorld &world, Shapes::Type shapeIdx, BodyType bodyType, const b2Vec2 &size);
    static Object objectGenerator(MyWorld &world, ObjectType objectType);

public:
    Object(MyWorld &world, ObjectType objectType)
        : Object{objectGenerator(world, objectType)} {}
    Shapes::Type getShapeIdx() const { return shapeIdx_; }
    const b2Vec2 &getPosition() const { return body_->GetPosition(); };
};

#endif