#ifndef WORLD_H
#define WORLD_H
#include "chunk.h"
#include <map>

class World
{
private:
    std::map<b2Vec2, std::unique_ptr<Chunk>> chunks;

public:
    World(b2World &world, int size);
    void clear();
    void draw(b2World &world, const Player &player);
    void spawnChunk(b2World &world, b2Vec2 position);
    void removeChunk(b2Vec2 position);
    b2Vec2 closestChunk(b2Vec2 position) const;
    b2Vec2 openChunk(b2Vec2 position) const;
};

#endif