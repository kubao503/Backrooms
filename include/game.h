#ifndef GAME_H
#define GAME_H

#include "object.h"

#include <box2d/box2d.h>
#include <set>
#include <memory>

class Game
{
private:
    std::set<Object *> freeItems_;

public:
    void createItem(b2World &world, Object::Type type, const b2Vec2 &position, float angle);
};

#endif
