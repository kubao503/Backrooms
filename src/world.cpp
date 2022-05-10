#include "world.h"
#include <iostream>

World::World(b2World &world, int size)
{
    for (float i = 0; i < size * 10; i += 10)
        for (float j = 0; j < size * 10; j += 10)
        {
            this->spawnChunk(world, b2Vec2(i, j));
        }
}

void World::spawnChunk(b2World &world, b2Vec2 position)
{
    chunks[position] = std::make_unique<Chunk>(world, position);
}

void World::removeChunk(b2Vec2 position)
{
    b2Vec2 foundPosition = this->closestChunk(position);

    if (foundPosition.IsValid())
        chunks.erase(foundPosition);
};

void World::clear()
{
    chunks.clear();
}

void World::draw(b2World &world, const Player &player)
{
    for (auto &chunk : chunks)
    {
        b2Vec2 distance = chunk.second.get()->getPosition() - player.getPosition();
        if (abs(distance.x) < 50.0f && abs(distance.y) < 50.0f)
        {
            if (chunk.second.get()->wasCleared())
                chunk.second.get()->restore(world);
        }
        else if (!chunk.second.get()->wasCleared())
            chunk.second.get()->clear();
    }
}

b2Vec2 World::closestChunk(b2Vec2 position) const
{
    for (auto &&chunk : chunks)
    {
        b2Vec2 chunkPosition = chunk.second->getPosition();

        if (position.x >= chunkPosition.x && position.x <= (chunkPosition.x + 10.0f))
            if (position.y >= chunkPosition.y && position.y <= (chunkPosition.y + 10.0f))
                return chunkPosition;
    }

    return b2Vec2(INFINITY, INFINITY);
}

b2Vec2 World::openChunk(b2Vec2 position) const
{
    std::vector<b2Vec2> routes;
    routes.reserve(4);

    b2Vec2 currentChunk = this->closestChunk(position);

    if (currentChunk.IsValid())
    {
        if (!chunks.at(currentChunk)->wallNorth)
            routes.push_back(this->closestChunk(b2Vec2(position.x + 10.0f, position.y)));

        if (!chunks.at(currentChunk)->wallWest)
            routes.push_back(this->closestChunk(b2Vec2(position.x, position.y - 10.0f)));

        b2Vec2 southChunk = this->closestChunk(b2Vec2(position.x - 10.0f, position.y));
        if (southChunk.IsValid() && !chunks.at(currentChunk)->wallNorth)
            routes.push_back(southChunk);

        b2Vec2 eastChunk = this->closestChunk(b2Vec2(position.x, position.y + 10.0f));
        if (eastChunk.IsValid() && !chunks.at(currentChunk)->wallWest)
            routes.push_back(eastChunk);

        if (!routes.size())
            return b2Vec2(INFINITY, INFINITY);

        int choice = int(Chunk::mt() % routes.size());
        // std::cerr << choice << std::endl;
        return routes[choice];
    }
    return b2Vec2(INFINITY, INFINITY);
}