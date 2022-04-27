#ifndef CHUNK_H
#define CHUNK_H

#include "object3d.h"
#include "constants.h"
#include <ctime>
#include <random>

class Chunk
{
private:
    std::unique_ptr<Object3D> wallNorth{nullptr};
    std::unique_ptr<Object3D> wallWest{nullptr};
    static std::mt19937 mt;

public:
    Chunk(MyWorld &world, b2Vec2 position);
};

#endif