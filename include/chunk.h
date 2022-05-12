#ifndef CHUNK_H
#define CHUNK_H

#include "object3d.h"
#include "player.h"
#include "myMath.h"
#include <limits>
#include <ctime>
#include <random>

class Chunk
{
    friend class World;

private:
    std::unique_ptr<Object3D> wallNorth{nullptr};
    std::unique_ptr<Object3D> wallWest{nullptr};
    bool cleared_{false};
    static std::mt19937 mt;
    const b2Vec2 position_;
    b2Vec2 getWallNorthPosition() const;
    b2Vec2 getWallWestPosition() const;

public:
    Chunk(b2World &world, b2Vec2 position);
    void restore(b2World &world);
    void clear();
    bool wasCleared() const { return cleared_; };
    b2Vec2 getPosition() const { return position_; };
    b2Vec2 getCenter() const;
};

#endif
