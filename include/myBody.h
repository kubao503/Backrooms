#ifndef MY_BODY_H
#define MY_BODY_H

#include <box2d/box2d.h>

class Object;

// Class deriving from b2Body with additional Object reference
class MyBody : public b2Body
{
public:
    MyBody(const b2BodyDef *bd, b2World *world, const Object &object)
        : b2Body{bd, world}, object_{object} {}
    const Object &getObject() { return object_; }

private:
    const Object &object_;
};

#endif