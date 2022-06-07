#ifndef CHUNK_H
#define CHUNK_H

#include "object3d.h"
#include "random_generator.h"
#include "myMath.h"
#include "config.h"
#include "mediator.h" // for notifying about item creation
#include "emf.h"
#include "page.h"

#include <limits>
#include <ctime>
#include <random>

class Chunk
{
    friend class World;

private:
    std::unique_ptr<Object3D>
        wallNorth_{nullptr};
    std::unique_ptr<Object3D> wallWest_{nullptr};
    bool hunt_{false};

    static std::mt19937 mt;
    static RandomGenerator chunkGenerator;
    static std::vector<b2Vec2> spawnedPages_;

    const b2Vec2 position_;
    b2Vec2 getWallNorthPosition() const;
    b2Vec2 getWallWestPosition() const;

public:
    Chunk(b2World &world, const b2Vec2 &position, Mediator &mediator);
    bool isHunt() const;
    b2Vec2 getPosition() const { return position_; };
};

#endif
