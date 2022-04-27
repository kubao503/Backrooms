#include "chunk.h"

std::mt19937 Chunk::mt(time(nullptr));

Chunk::Chunk(MyWorld &world, b2Vec2 position)
{
    int seed = int(mt() % 4);

    b2Vec2 offsetWall = b2Vec2(position.x + 5.0f, position.y + 5.0f);

    // wallNorth = std::make_unique<Object3D>(world, Object::ObjectType::WALL, position, 0);
    // wallWest = std::make_unique<Object3D>(world, Object::ObjectType::WALL, offsetWall, PI / 2);

    // seed = 3;
    switch (seed)
    {
    case 1:
        wallNorth = std::make_unique<Object3D>(world, Object::ObjectType::WALL, position, 0);
        break;
    case 2:
        wallWest = std::make_unique<Object3D>(world, Object::ObjectType::WALL, offsetWall, PI / 2);
        break;
    case 3:
        wallNorth = std::make_unique<Object3D>(world, Object::ObjectType::WALL, position, 0);
        wallWest = std::make_unique<Object3D>(world, Object::ObjectType::WALL, offsetWall, PI / 2);
        break;
    default:
        break;
    }
};