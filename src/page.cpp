#include "page.h"

unsigned int Page::pickedPages_{0};

Page::Page(b2World &world, const b2Vec2 &position, float angle, Mediator &mediator)
    : Item{world, Type::PAGE, Image::EMPTY, position, angle, mediator} {}

void Page::picked()
{
    pickedPages_++;
}