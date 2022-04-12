#ifndef MY_WORLD_H
#define MY_WORLD_H

#include "myBody.h"
#include <box2d/box2d.h>
#include <new>  // for operator new(sizetype, void*&)

class Object;

class MyWorld : public b2World
{
public:
    MyBody *CreateBody(const b2BodyDef *def, const Object &object);
};

#endif