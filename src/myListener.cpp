#include "myListener.h"

#include "gameState.h" // for sharing item

MyListener::MyListener(GameState &game)
    : game_{game} {}

void MyListener::BeginContact(b2Contact *contact)
{
    Object *objA = (Object *)contact->GetFixtureA()->GetBody()->GetUserData().pointer;
    Object *objB = (Object *)contact->GetFixtureB()->GetBody()->GetUserData().pointer;
    bool isSensorA{contact->GetFixtureA()->IsSensor()};
    bool isSensorB{contact->GetFixtureB()->IsSensor()};

    if (getTandU<Player, Object2D>(objA, objB, isSensorA, isSensorB))
    {
        // collision with Player camera
        if (isSensorA)
        {
            // Object goes inside field of view
            if (game_.debugGet())
                std::cerr << "object observed\n";

            static_cast<Player *>(objA)->objectObserved(static_cast<Object2D *>(objB));
            return;
        }

        // collision with Player actual body

        if (getTandU<Player, Enemy>(objA, objB, isSensorA, isSensorB))
        {
            // killing Player
            if (game_.debugGet())
                std::cerr << "YOU FOOL YOU DIED\n";

            game_.gameOver();
            return;
        }
        else if (getTandU<Player, Item>(objA, objB, isSensorA, isSensorB))
        {
            // item near
            if (game_.debugGet())
                std::cerr << "Item contact\n";

            static_cast<Player *>(objA)->itemContact(game_.shareObject<Item>(static_cast<Item *>(objB)));
            return;
        }
    }

    if (game_.debugGet())
        std::cerr << "Unindentified collision\n";
}

void MyListener::EndContact(b2Contact *contact)
{
    Object *objA = (Object *)contact->GetFixtureA()->GetBody()->GetUserData().pointer;
    Object *objB = (Object *)contact->GetFixtureB()->GetBody()->GetUserData().pointer;
    bool isSensorA{contact->GetFixtureA()->IsSensor()};
    bool isSensorB{contact->GetFixtureB()->IsSensor()};

    if (getTandU<Player, Object2D>(objA, objB, isSensorA, isSensorB))
    {
        if (isSensorA)
        {
            // Object goes out of field of view
            if (game_.debugGet())
                std::cerr << "object lost\n";

            static_cast<Player *>(objA)->objectLost(static_cast<Object2D *>(objB));
            return;
        }

        // end of collision with Player actual body

        if (getTandU<Player, Item>(objA, objB, isSensorA, isSensorB))
        {
            // Player leaving item
            if (game_.debugGet())
                std::cerr << "Item lost\n";

            static_cast<Player *>(objA)->itemLost();
            return;
        }

        if (game_.debugGet())
            std::cerr << "Unindentified collision end\n";
    }
}

template <typename T, typename U>
bool MyListener::getTandU(Object *&objA, Object *&objB, bool &isSensorA, bool &isSensorB)
{
    if (dynamic_cast<T *>(objA) && dynamic_cast<U *>(objB))
        return true;

    if (dynamic_cast<U *>(objA) && dynamic_cast<T *>(objB))
    {
        std::swap(objA, objB);
        std::swap(isSensorA, isSensorB);
        return true;
    }

    return false;
}
