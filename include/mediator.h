#ifndef MEDIATOR_H
#define MEDIATOR_H

class Component;

class Mediator
{
public:
    enum Event
    {
        GAMEOVER,
        ITEM_CONTACT,
        TOTAL
    };

    virtual void notify(const Component &comp, Event event) = 0;
};

#endif
