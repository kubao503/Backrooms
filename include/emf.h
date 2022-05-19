#ifndef EMF_H
#define EMF_H

#include "item.h"   // for inheritance
#include "myMath.h" // for calculating distance to enemy

#include <array>    // for storing emf shapes

class Emf : public Item
{
private:
    static constexpr float detectionRadius{50.0f};
    static constexpr unsigned int statesNumber{4};
    static constexpr std::array<Shapes::Type, statesNumber> emfShapes_{
        Shapes::EMF,
        Shapes::EMF1,
        Shapes::EMF2,
        Shapes::EMF3};
    // bool on_{false};

public:
    Emf(b2World &world, const b2Vec2 &position, float angle, Mediator& mediator);
    void drop(b2World &world, const Object &player) override;

    void action(const b2Vec2 &playerPos) override;
};

#endif
