#include "chunk.h"
#include <iostream>

std::mt19937 Chunk::mt(time(nullptr));

Chunk::Chunk(b2World &world, b2Vec2 position)
    : position_(position)
{
    int seed = int(mt() % 4);

    b2Vec2 wallWestPosition = b2Vec2(position_.x + 10.0f, position_.y + 5.0f);
    b2Vec2 wallNorthPosition = b2Vec2(position_.x + 5.0f, position_.y);

    // wallNorth = std::make_unique<Object3D>(world, Object::Type::WALL, position, 0);
    // wallWest = std::make_unique<Object3D>(world, Object::Type::WALL, offsetWall, PI / 2);

    // seed = 3; // DEBUG
    switch (seed)
    {
    case 1:
        wallNorth = std::make_unique<Object3D>(world, Object::Type::WALL, wallNorthPosition, 0);
        break;
    case 2:
        wallWest = std::make_unique<Object3D>(world, Object::Type::WALL, wallWestPosition, PI / 2);
        break;
    case 3:
        wallNorth = std::make_unique<Object3D>(world, Object::Type::WALL, wallNorthPosition, 0);
        wallWest = std::make_unique<Object3D>(world, Object::Type::WALL, wallWestPosition, PI / 2);
        break;
    default:
        break;
    }
}

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
        // std::cerr << wallNorth.get()->getAngle();
        b2Vec2 wallNorthPosition = b2Vec2(position_.x + 5.0f, position_.y);
        wallNorth->setBody(world, Object::Type::WALL, wallNorthPosition, 0);
    }

    if (wallWest)
    {
        b2Vec2 wallWestPosition = b2Vec2(position_.x + 10.0f, position_.y + 5.0f);
        wallWest->setBody(world, Object::Type::WALL, wallWestPosition, PI / 2);
    }
}

b2Vec2 Chunk::getClosestChunk(const b2Vec2 &position) const
{
    if (position.x >= this->getPosition().x && position.x <= (this->getPosition().x + 10.0f))
        if (position.y >= this->getPosition().y && position.y <= (this->getPosition().y + 10.0f))
            return this->getPosition();
    return b2Vec2();
};
