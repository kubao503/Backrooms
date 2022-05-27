#ifndef COMPONENT_H
#define COMPONENT_H

#include "mediator.h"

class Component
{
protected:
    Mediator &mediator_;

public:
    virtual ~Component() = default;
    Component(Mediator &mediator)
        : mediator_{mediator} {}
};

#endif
