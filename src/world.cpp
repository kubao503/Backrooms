#include "world.h"
#include <iostream>

World::World(b2World &world, unsigned int size, const b2Vec2 &playerPosition)
{
    (void)world;
    (void)size;
    (void)playerPosition;
    // for (float i = playerPosition.x - size * Conf::chunkWidth; i < playerPosition.x + size * Conf::chunkWidth; i += Conf::chunkWidth)
    //     for (float j = playerPosition.y - size * Conf::chunkWidth; j < playerPosition.y + size * Conf::chunkWidth; j += Conf::chunkWidth)
    //     {
    //         spawnChunk(world, b2Vec2(i, j));
    //     }
}

void World::spawnChunk(b2World &world, const b2Vec2 &position)
{
    chunks[position] = std::make_unique<Chunk>(world, position);
}

void World::removeChunk(const b2Vec2 &position)
{
    b2Vec2 foundPosition = closestChunk(position);

    if (foundPosition.IsValid())
        chunks.erase(foundPosition);
}

void World::clear()
{
    chunks.clear();
}

void World::draw(b2World &world, const b2Vec2 &playerPosition)
{
    int normalizedX = round(playerPosition.x / Conf::chunkWidth) * Conf::chunkWidth;
    int normalizedY = round(playerPosition.y / Conf::chunkWidth) * Conf::chunkWidth;

    float renderFactor = 1.5;

    for (float i = normalizedX - Conf::renderDistance * renderFactor; i < normalizedX + Conf::renderDistance * renderFactor; i += Conf::chunkWidth)
        for (float j = normalizedY - Conf::renderDistance * renderFactor; j < normalizedY + Conf::renderDistance * renderFactor; j += Conf::chunkWidth)
        {
            try
            {
                chunks.at(b2Vec2(i, j));
            }
            catch (const std::out_of_range &exception)
            {
                spawnChunk(world, b2Vec2(i, j));
            }
        }

    for (auto it = chunks.begin(); it != chunks.end();)
    {
        b2Vec2 distance = it->second.get()->getPosition() - playerPosition;

        if (distance.Length() > Conf::renderDistance * renderFactor)
            it = chunks.erase(it);
        else
            ++it;
    }
}

b2Vec2 World::closestChunk(const b2Vec2 &position) const
{
    int normalizedX = round(position.x / Conf::chunkWidth) * Conf::chunkWidth;
    int normalizedY = round(position.y / Conf::chunkWidth) * Conf::chunkWidth;
    b2Vec2 chunkPosition = b2Vec2(normalizedX, normalizedY);

    try
    {
        chunks.at(chunkPosition); // If chunk exists, return it
        return chunkPosition;
    }
    catch (const std::out_of_range &exception)
    {
    }
    return b2Vec2(INFINITY, INFINITY);
}

b2Vec2 World::openChunk(const b2Vec2 &position, Directions &prefDirection) const
{
    Directions unprefDirection = static_cast<Directions>(prefDirection * (-1)); // Reverses preffered direction

    std::vector<std::pair<Directions, b2Vec2>> routes;
    routes.reserve(4);

    b2Vec2 currentChunk = this->closestChunk(position);

    if (currentChunk.IsValid())
    {
        b2Vec2 neighbourChunk = this->closestChunk(b2Vec2(position.x + Conf::chunkWidth, position.y));
        if (neighbourChunk.IsValid() && !chunks.at(currentChunk)->wallNorth_) // Checks north route
            routes.push_back({N, neighbourChunk});

        neighbourChunk = this->closestChunk(b2Vec2(position.x, position.y - Conf::chunkWidth));
        if (neighbourChunk.IsValid() && !chunks.at(currentChunk)->wallWest_) // Checks west route
            routes.push_back({W, neighbourChunk});

        neighbourChunk = this->closestChunk(b2Vec2(position.x - Conf::chunkWidth, position.y));
        if (neighbourChunk.IsValid() && !chunks.at(neighbourChunk)->wallNorth_) // Checks south route
            routes.push_back({S, neighbourChunk});

        neighbourChunk = this->closestChunk(b2Vec2(position.x, position.y + Conf::chunkWidth));
        if (neighbourChunk.IsValid() && !chunks.at(neighbourChunk)->wallWest_) // Checks east route
            routes.push_back({E, neighbourChunk});

        if (!routes.size()) // If no choice is available, return not valid vector
            return b2Vec2(INFINITY, INFINITY);

        if (routes.size() > 1) // If there is more than one choice available, remove unpreffered direction from choices pool
        {
            std::remove_if(
                routes.begin(), routes.end(), [unprefDirection](auto &route)
                { return unprefDirection == route.first; });
        }

        int choice = int(Chunk::mt() % 2); // Choice for choosing preffered route

        if (!choice) // If preffered direction is available as choice (and choice equals 0), return it
        {
            auto it = std::find_if(routes.begin(), routes.end(), [prefDirection](auto &route)
                                   { return prefDirection == route.first; });

            if (it != routes.end())
            {
                prefDirection = it->first;
                return it->second;
            }
        }

        choice = int(Chunk::mt() % routes.size()); // Choice for choosing from available routes if preffered route was not taken

        prefDirection = routes[choice].first; // Set new preffered route and return chunk's coordinates
        return routes[choice].second;
    }
    return b2Vec2(INFINITY, INFINITY);
}

// template <typename T>
// void World::createItem(b2World &world, Object::Type type, const b2Vec2 &position, float angle)
// {
//     if (type == Object::Type::EMF)
//         objects_.emplace(std::make_shared<Emf>(world, position, angle));
// }
