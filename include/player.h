#ifndef PLAYER_H
#define PLAYER_H

#include "userio.h" // for getting mouse input
#include "object.h" // for inheriting form Object
#include "myMath.h" // for rotating vector
#include "item.h"   // for picking up item
#include "world.h"  // for getting items

#include <box2d/box2d.h> // for setting b2Body velocity
#include <vector>        // for storing visible objects
#include <memory> // for storing items in shared ptr

class Player : public Object
{
private:
    // Sets velocity based on the local cooridinates
    void setLocalVelocity(const b2Vec2 &newVelocity);
    void move();
    void lookAround(UserIO &userIO);
    void itemOperations(UserIO &userIO, World &world);
    void debugUpdate(UserIO &userIO, World &world);

    // Stores any items that are near
    std::vector<const Object2D *> visibleObjects_;
    const Item *nearbyItem_;
    std::vector<std::shared_ptr<Item>> ownedItems_;
    unsigned int currentItemIdx_{0};

public:
    Player(b2World &world, const b2Vec2 &position, float angle);

    void control(UserIO &userIO, World &world);

    const std::vector<const Object2D *> &getVisibleObjects() const;
    const std::vector<std::shared_ptr<Item>> &getOwnedItems() const { return ownedItems_; }
    const Item *getCurrentItem() const { return ownedItems_[currentItemIdx_].get(); }
    void doItemAction(const b2World &world) const;

    void objectObserved(const Object2D *object);
    void objectLost(const Object2D *object);

    void itemContact(const Item *item);
    void itemLost();
};

#endif
