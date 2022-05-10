#ifndef EMF_H
#define EMF_H

#include "item.h"   // for inheritance
#include "enemy.h"  // for finding closest enemy
#include "myMath.h" // for calculating distance to enemy

class Emf : public Item
{
private:
    class EnemyCallback : public b2QueryCallback
    {
    private:
        const Enemy *foundEnemy_{nullptr};
        bool ReportFixture(b2Fixture *fixture) override;

    public:
        const Enemy *getEnemy() { return foundEnemy_; }
    };

    static constexpr float aabbSize{50.0f};
    static constexpr unsigned int emfStates{4};
    static constexpr Shapes::Type emfShapes_[emfStates]{
        Shapes::EMF,
        Shapes::EMF1,
        Shapes::EMF2,
        Shapes::EMF3};
    bool on_{false};

public:
    Emf(b2World &world, const b2Vec2 &position, float angle);
    void drop(b2World &world, const Object &player);

    void action(const b2World &world, const Object &player) override;
};

#endif
