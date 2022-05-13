#ifndef GAME_H
#define GAME_H

#include "object.h"
#include "emf.h"

#include <box2d/box2d.h>
#include <set>
#include <memory>

class Game
{
private:
    std::set<std::shared_ptr<Object>> objects_;
    bool debugMode_{false};

public:
    template <class T>
    std::shared_ptr<T> shareObject(const T *searchedObj)
    {
        for (auto obj : objects_)
        {
            if (obj.get() == searchedObj)
            {
                return std::static_pointer_cast<T>(obj);
            }
        }

        return nullptr;
    }

    bool debugGet() const { return debugMode_; }
    void debugSet(bool debug) { debugMode_ = debug; }
    void createItem(b2World &world, Object::Type type, const b2Vec2 &position, float angle);
};

#endif
