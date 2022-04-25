#ifndef MY_BODY_H
#define MY_BODY_H

#include <box2d/box2d.h>    // for b2Body

class Object3D;

// Class deriving from b2Body with additional Object3D reference
class MyBody : public b2Body
{
public:
    MyBody(const b2BodyDef *bd, b2World *world, const Object3D &object)
        : b2Body{bd, world}, object_{object} {}
    const Object3D &getObject() { return object_; }

private:
    const Object3D &object_;
};

#endif