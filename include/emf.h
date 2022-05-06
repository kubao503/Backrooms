#ifndef EMF_H
#define EMF_H

#include "item.h"
#include "enemy.h"
#include "player.h"

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
    static constexpr unsigned int emfStates{2};
    static constexpr Shapes::Type emfShapes_[emfStates]{
        Shapes::EMF,
        Shapes::EMF1};
    bool on_{false};

public:
    Emf(b2World &world, const b2Vec2 &position, float angle);
    void action(const b2World &world, const Player &player) override;
};

#endif
