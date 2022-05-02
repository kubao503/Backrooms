#ifndef PLAYER_H
#define PLAYER_H

#include "userio.h"   // for getting mouse input
#include "object2d.h" // for inheriting form Object2D
#include "myMath.h"   // for rotating vector
#include "item.h"     // for picking up item

#include <box2d/box2d.h> // for setting b2Body velocity
#include <set>           // for storing near items

class Player : public Object2D
{
private:
    // Sets velocity based on the local cooridinates
    void setLocalVelocity(const b2Vec2 &newVelocity);

    // Stores any items that are near
    std::set<const Item *> nearItems_;

public:
    Player(b2World &world, ObjectType objectType, const b2Vec2 &position, float angle)
        : Object2D{world, objectType, position, angle} {}

    void control(UserIO &userIO);
    void itemContact(const Item *item);
    void itemLost(const Item *item);
};

#endif
