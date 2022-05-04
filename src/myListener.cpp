#include "myListener.h"

void MyListener::BeginContact(b2Contact *contact)
{
    Object *objA = (Object *)contact->GetFixtureA()->GetBody()->GetUserData().pointer;
    Object *objB = (Object *)contact->GetFixtureB()->GetBody()->GetUserData().pointer;

    if (getTandU<Player, Object2D>(objA, objB))
    {
        if (contact->GetFixtureA()->IsSensor())
        {
            // collision with Player camera
            // Object goes inside field of view
            static_cast<Player *>(objA)->objectObserved(static_cast<Object2D *>(objB));
            return;
        }

        // collision with Player actual body

        if (getTandU<Player, Enemy>(objA, objB))
        {
            // killing Player
            std::cerr << "YOU FOOL YOU DIED\n";
            return;
        }
        else if (getTandU<Player, Item>(objA, objB))
        {
            // item near
            static_cast<Player *>(objA)->itemContact(static_cast<Item *>(objB));
            return;
        }
    }

    std::cerr << "Unindentified collision\n";
}

void MyListener::EndContact(b2Contact *contact)
{
    Object *objA = (Object *)contact->GetFixtureA()->GetBody()->GetUserData().pointer;
    Object *objB = (Object *)contact->GetFixtureB()->GetBody()->GetUserData().pointer;

    if (getTandU<Player, Object2D>(objA, objB))
    {
        if (contact->GetFixtureA()->IsSensor())
        {
            // Object goes out of field of view
            static_cast<Player *>(objA)->objectLost(static_cast<Object2D *>(objB));
            return;
        }

        // end of collision with Player actual body

        if (getTandU<Player, Item>(objA, objB))
        {
            // Player leaving item
            static_cast<Player *>(objA)->itemLost();
            return;
        }

        std::cerr << "Unindentified collision end\n";
    }
}

template <typename T, typename U>
bool MyListener::getTandU(Object *&objA, Object *&objB)
{
    T *tPtr = dynamic_cast<T *>(objA);
    U *uPtr = dynamic_cast<U *>(objB);

    if (tPtr && uPtr)
        return true;

    tPtr = dynamic_cast<T *>(objB);
    uPtr = dynamic_cast<U *>(objA);

    if (tPtr && uPtr)
        return true;

    return false;
}
