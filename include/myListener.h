#ifndef MY_LISTENER_H
#define MY_LISTENER_H

#include "enemy.h" // for dynamic cast

#include <box2d/box2d.h> // for inheriting from b2ContactListener

#include <iostream> // DEBUG

class MyListener : public b2ContactListener
{
    void BeginContact(b2Contact *contact) override
    {
        Object *objA = (Object *)contact->GetFixtureA()->GetBody()->GetUserData().pointer;
        Object *objB = (Object *)contact->GetFixtureB()->GetBody()->GetUserData().pointer;

        if ((dynamic_cast<Enemy *>(objA) && dynamic_cast<Player *>(objB)) || (dynamic_cast<Player *>(objA) && dynamic_cast<Enemy *>(objB)))
        {
            std::cerr << "YOU FOOL YOU DIED\n";
        }
    }
};

#endif
