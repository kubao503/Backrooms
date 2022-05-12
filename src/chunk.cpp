#include "chunk.h"
#include <iostream>

std::mt19937 Chunk::mt(time(nullptr));

Chunk::Chunk(b2World &world, const b2Vec2 &position)
    : position_(position)
{
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
};
b2Vec2 Chunk::getWallWestPosition() const
{
    return b2Vec2(position_.x, position_.y - Conf::chunkWidth / 2);
};

void Chunk::clear()
{
    cleared_ = true;

    if (wallNorth)
        wallNorth->destroyBody();
    if (wallWest)
        wallWest->destroyBody();
}

void Chunk::restore(b2World &world)
{
    cleared_ = false;

    if (wallNorth)
    {
        b2Vec2 wallNorthPosition = this->getWallNorthPosition();
        wallNorth->setBody(world, Object::Type::WALL, wallNorthPosition, PI / 2);
    }

    if (wallWest)
    {
        b2Vec2 wallWestPosition = this->getWallWestPosition();
        wallWest->setBody(world, Object::Type::WALL, wallWestPosition, 0);
    }
}

b2Vec2 Chunk::getCenter() const
{
    return b2Vec2(position_.x + Conf::chunkWidth / 2, position_.y + Conf::chunkWidth / 2);
}
