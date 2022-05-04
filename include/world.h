#ifndef WORLD_H
#define WORLD_H
#include "chunk.h"

class World
{
private:
    std::vector<Chunk> chunks;

public:
    World(b2World &world, int size);
    void clear();
    void draw(b2World &world, const Player &player);
    b2Vec2 closestChunk(const Player &player) const;
};

#endif