#include "chunk.h"
#include <iostream>

std::mt19937 Chunk::mt(time(nullptr));
RandomGenerator Chunk::chunkGenerator{int(mt())};

Chunk::Chunk(b2World &world, const b2Vec2 &position)
    : position_(position)
{
    b2Vec2 bigChunkPosition = b2Vec2(round(position.x / Conf::bigChunkWidth), round(position.y / Conf::bigChunkWidth));
    chunkGenerator.seed(int(bigChunkPosition.x), int(bigChunkPosition.y));
    bool lowerDensity = chunkGenerator.drawLots(1u, 11u);

    chunkGenerator.seed(int(position.x), int(position.y));
    unsigned int wallChance{lowerDensity ? 1u : 4u};

    bool wallNorthExists = chunkGenerator.drawLots(wallChance, 10u);
    bool wallWestExists = chunkGenerator.drawLots(wallChance, 10u);
    bool huntExists = chunkGenerator.drawLots(1u, 10u);

    b2Vec2 wallNorthPosition = this->getWallNorthPosition();
    b2Vec2 wallWestPosition = this->getWallWestPosition();

    if (wallNorthExists)
        wallNorth_ = std::make_unique<Object3D>(world, Object::Type::WALL, wallNorthPosition, PI / 2);

    if (wallWestExists)
        wallWest_ = std::make_unique<Object3D>(world, Object::Type::WALL, wallWestPosition, 0);

    if (huntExists)
        hunt_ = true;

    return;
}

b2Vec2 Chunk::getWallNorthPosition() const
{
    return b2Vec2(position_.x + Conf::chunkWidth / 2, position_.y);
}

b2Vec2 Chunk::getWallWestPosition() const
{
    return b2Vec2(position_.x, position_.y - Conf::chunkWidth / 2);
}

bool Chunk::isHunt() const
{
    return hunt_;
}