#ifndef WORLD_H
#define WORLD_H
#include "chunk.h"
#include <map>

class World
{
private:
    std::map<b2Vec2, std::unique_ptr<Chunk>> chunks;

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
};

#endif