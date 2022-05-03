#include "chunk.h"
#include <iostream>

std::mt19937 Chunk::mt(time(nullptr));

Chunk::Chunk(b2World &world, b2Vec2 position)
    : position_(position)
{
    int seed = int(mt() % 4);

    b2Vec2 offsetPosition = b2Vec2(position.x + 5.0f, position.y + 5.0f);

    // wallNorth = std::make_unique<Object3D>(world, Object::Type::WALL, position, 0);
    // wallWest = std::make_unique<Object3D>(world, Object::Type::WALL, offsetWall, PI / 2);

    // seed = 2;      // DEBUG
    switch (seed)
    {
    case 1:
        wallNorth = std::make_unique<Object3D>(world, Object::Type::WALL, position, 0);
        break;
    case 2:
        wallWest = std::make_unique<Object3D>(world, Object::Type::WALL, offsetPosition, PI / 2);
        break;
    case 3:
        wallNorth = std::make_unique<Object3D>(world, Object::Type::WALL, position, 0);
        wallWest = std::make_unique<Object3D>(world, Object::Type::WALL, offsetPosition, PI / 2);
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
        wallNorth->setBody(world, Object::Type::WALL, position_, 0);
    }

    if (wallWest)
    {
        b2Vec2 offsetPosition = b2Vec2(position_.x + 5.0f, position_.y + 5.0f);
        wallWest->setBody(world, Object::Type::WALL, offsetPosition, PI / 2);
    }
}
