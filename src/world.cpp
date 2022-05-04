#include "world.h"

World::World(b2World &world, int size)
{
    for (float i = 0; i < size * 10; i += 10)
        for (float j = 0; j < size * 10; j += 10)
        {
            chunks.push_back(Chunk(world, b2Vec2(i, j)));
        }

    this->clear();
}

void World::clear()
{
    for (auto &chunk : chunks)
    {
        chunk.clear();
    }
}

void World::draw(b2World &world, const Player &player)
{
    for (auto &chunk : chunks)
    {
        b2Vec2 distance = chunk.getPosition() - player.getPosition();
        if (abs(distance.x) < 50.0f && abs(distance.y) < 50.0f)
        {
            if (chunk.wasCleared())
                chunk.restore(world);
        }
        else if (!chunk.wasCleared())
            chunk.clear();
    }
}

b2Vec2 World::closestChunk(const Player &player) const
{
    for (auto &chunk : chunks)
    {
        b2Vec2 playerPosition = player.getPosition();
        b2Vec2 chunkPosition = chunk.getPosition();

        if (playerPosition.x >= chunkPosition.x && playerPosition.x <= (chunkPosition.x + 10.0f))
            if (playerPosition.y >= chunkPosition.y && playerPosition.y <= (chunkPosition.y + 10.0f))
                return chunk.getPosition();
    }

    return b2Vec2(INFINITY, INFINITY);
}
