#ifndef OBJECT_H
#define OBJECT_H

#include "myMath.h"
#include "config.h"

#include <box2d/box2d.h> // for creating body

#include <memory>     // for b2Body smart pointer
#include <functional> // for storing fixture calls

// Collidable
class Object
{
public:
    enum ObjectType
    {
        WALL,
        RED_WALL,
        PLAYER,
        ENEMY,
        ITEM,
        CAMERA,
        TOTAL
    };

private:
    // Object generating methods
    static const b2BodyDef &getBodyDef(b2BodyType bodyType);
    static const b2Shape &getShape(float halfX, float halfY);
    static const b2Shape &getShape(float radius);
    static const b2Shape &getShape(float FOVangle, float renderDist, int verticesCount);
    static const b2FixtureDef &getFixtureDef(const b2Shape &shape);
    // Returns unique position helping avoiding spawning objects at the same place
    b2Vec2 getNewPosition() const;

    friend class Arguments;

    struct Arguments
    {
        b2BodyType bodyType_;
        b2FixtureDef fixDef_;
        Arguments(b2BodyType bodyType, const b2Shape &shape);
    };

    // Arguments for creating objects
    static Arguments argList[ObjectType::TOTAL];

protected:
    std::unique_ptr<b2Body> body_{nullptr};

    virtual ~Object()
    {
        if (body_)
            destroyBody();
    }
    Object(b2World &world, ObjectType type);
    Object(b2World &world, ObjectType type, const b2Vec2 &position, float angle);
    void setBody(b2World &world, ObjectType type, const b2Vec2 &position, float angle);
    void destroyBody();
    void setSensor(bool sensor);

public:
    const b2Vec2 &getPosition() const { return body_->GetPosition(); };
    float getAngle() const { return body_->GetAngle(); };
};

#endif
