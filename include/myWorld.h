#ifndef MY_WORLD_H
#define MY_WORLD_H

#include "myBody.h" // for creating MyBody
#include <box2d/box2d.h>    // for inheriting from b2World
#include <memory>   // for b2Body smart pointer
#include <new>      // for operator new(sizetype, void*&)

// DEBUG
// #include <iostream>

class Object;

class MyWorld : public b2World
{
public:
    MyWorld(const b2Vec2 &gravity) : b2World{gravity} {}
    std::unique_ptr<b2Body> CreateBody(const b2BodyDef *def, const Object3D &object);
};

#endif
