#ifndef MEDIATOR_H
#define MEDIATOR_H

struct b2Vec2;
class Component;

class Mediator
{
public:
    enum Event
    {
        GAMEOVER,
        ITEM_CONTACT,
        ITEM_CREATED,
        TOTAL
    };

    virtual void notify(const Component &comp, Event event) = 0;
    virtual void notify(std::shared_ptr<Component> comp, Event event) = 0;
    virtual bool enemySpawned() const = 0;
    virtual const b2Vec2 &enemyPosition() const = 0;
};

#endif
