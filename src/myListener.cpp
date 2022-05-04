#include "myListener.h"

void MyListener::BeginContact(b2Contact *contact)
{
    Object *objA = (Object *)contact->GetFixtureA()->GetBody()->GetUserData().pointer;
    Object *objB = (Object *)contact->GetFixtureB()->GetBody()->GetUserData().pointer;

    // Enemy killing player
    if (getTandU<Player, Enemy>(objA, objB))
    {
        std::cerr << "YOU FOOL YOU DIED\n";
        return;
    }

    // Player being near item
    if (getTandU<Player, Item>(objA, objB))
    {
        static_cast<Player *>(objA)->itemContact(static_cast<Item *>(objB));
        return;
    }

    // Object goes inside field of view
    if (getTandU<Camera, Object2D>(objA, objB))
    {
        static_cast<Camera *>(objA)->objectObserved(static_cast<Object2D *>(objB));
        return;
    }

    std::cerr << "Unindentified collision\n";
}

void MyListener::EndContact(b2Contact *contact)
{
    Object *objA = (Object *)contact->GetFixtureA()->GetBody()->GetUserData().pointer;
    Object *objB = (Object *)contact->GetFixtureB()->GetBody()->GetUserData().pointer;

    // Player leaving item
    if (getTandU<Player, Item>(objA, objB))
    {
        static_cast<Player *>(objA)->itemLost(static_cast<Item *>(objB));
        return;
    }

    // Object goes out of field of view
    if (getTandU<Camera, Object2D>(objA, objB))
    {
        static_cast<Camera *>(objA)->objectLost(static_cast<Object2D *>(objB));
        return;
    }

    std::cerr << "Unindentified collision end\n";
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
