#ifndef MY_LISTENER_H
#define MY_LISTENER_H

#include "enemy.h" // for dynamic cast
#include "player.h"
#include "item.h"
#include "camera.h"

#include <box2d/box2d.h> // for inheriting from b2ContactListener

#include <iostream> // printing death message

class MyListener : public b2ContactListener
{
    void BeginContact(b2Contact *contact) override;
    void EndContact(b2Contact *contact) override;

    template <typename T, typename U>
    bool getTandU(Object *&objA, Object *&objB);
};

#endif
