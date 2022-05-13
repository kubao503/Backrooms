#include "chunk.h"
#include <iostream>

std::mt19937 Chunk::mt(time(nullptr));

Chunk::Chunk(b2World &world, const b2Vec2 &position)
    : position_(position)
{
    if (int(mt()) % 10)
        hunt_ = true;

    int seed = int(mt() % 5);

    b2Vec2 wallWestPosition = this->getWallWestPosition();
    b2Vec2 wallNorthPosition = this->getWallNorthPosition();

    switch (seed)
    {
    case 1:
        wallNorth = std::make_unique<Object3D>(world, Object::Type::WALL, wallNorthPosition, PI / 2);
        break;
    case 2:
        wallWest = std::make_unique<Object3D>(world, Object::Type::WALL, wallWestPosition, 0);
        break;
    case 3:
        wallNorth = std::make_unique<Object3D>(world, Object::Type::WALL, wallNorthPosition, PI / 2);
        wallWest = std::make_unique<Object3D>(world, Object::Type::WALL, wallWestPosition, 0);
        break;
    default:
        break;
    }
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