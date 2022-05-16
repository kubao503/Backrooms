#ifndef MY_LISTENER_H
#define MY_LISTENER_H

#include "enemy.h" // for dynamic cast
#include "player.h"
#include "item.h"

#include <box2d/box2d.h> // for inheriting from b2ContactListener

#include <iostream> // printing death message

// #include "gameState.h" // circular include
class GameState;

class MyListener : public b2ContactListener
{
public:
    MyListener(const GameState &game);

private:
    void BeginContact(b2Contact *contact) override;
    void EndContact(b2Contact *contact) override;

    template <typename T, typename U>
    bool getTandU(Object *&objA, Object *&objB, bool &isSensorA, bool &isSensorB);

    const GameState &game_;
};

#endif
