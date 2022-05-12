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
    int normalizedX = round(position.x / 10) * 10;
    int normalizedY = round(position.y / 10) * 10;
    b2Vec2 chunkPosition = b2Vec2(normalizedX, normalizedY);

    try
    {
        chunks.at(chunkPosition);
        return chunkPosition;
    }
    catch (std::out_of_range)
    {
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
        b2Vec2 neighbourChunk = this->closestChunk(b2Vec2(position.x + Conf::chunkWidth, position.y));
        if (neighbourChunk.IsValid() && !chunks.at(currentChunk)->wallNorth)
            routes.push_back(neighbourChunk);

        neighbourChunk = this->closestChunk(b2Vec2(position.x, position.y - Conf::chunkWidth));
        if (!chunks.at(currentChunk)->wallWest)
            routes.push_back(neighbourChunk);

        neighbourChunk = this->closestChunk(b2Vec2(position.x - Conf::chunkWidth, position.y));
        if (neighbourChunk.IsValid() && !chunks.at(neighbourChunk)->wallNorth)
            routes.push_back(neighbourChunk);

        neighbourChunk = this->closestChunk(b2Vec2(position.x, position.y + Conf::chunkWidth));
        if (neighbourChunk.IsValid() && !chunks.at(neighbourChunk)->wallWest)
            routes.push_back(neighbourChunk);

        if (!routes.size())
            return b2Vec2(INFINITY, INFINITY);

        // for (auto &it : routes)
        // {
        //     std::cerr << it.x << " " << it.y << std::endl;
        // }

        int choice = int(Chunk::mt() % routes.size());
        return routes[choice];
    }
    return b2Vec2(INFINITY, INFINITY);
}