#ifndef WORLD_H
#define WORLD_H

#include "object.h"
#include "chunk.h"

#include <set>      // for string objects
#include <map>      // for storing chunks

class World
{
private:
    std::map<b2Vec2, std::unique_ptr<Chunk>> chunks;
    std::set<std::shared_ptr<Object>> objects_;
    bool debugMode_{false};

public:
    enum Directions
    {
        N = -1,
        S = 1,
        W = -2,
        E = 2
    };

    World(b2World &world, unsigned int size, const b2Vec2 &playerPosition);
    void clear();
    void draw(b2World &world, const b2Vec2 &playerPosition);
    void spawnChunk(b2World &world, const b2Vec2 &position);
    void removeChunk(const b2Vec2 &position);
    b2Vec2 closestChunk(const b2Vec2 &position) const;
    b2Vec2 openChunk(const b2Vec2 &position, Directions &prefDirection) const;

    template <typename T>
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
    // template <typename T>
    // void createItem(b2World &world, Object::Type type, const b2Vec2 &position, float angle);
};

#endif
