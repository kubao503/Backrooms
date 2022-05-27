#include "item.h"

Item::Item(b2World &world, Type type, Image::Type GUIShapeIdx, const b2Vec2 &position, float angle, Mediator &mediator)
    : Object2D{world, type, position, angle}, Component{mediator}, GUIShapeIdx_{GUIShapeIdx}
{
    setSensor(true);

    addFixture(Type::ITEM_PICK_AREA, Category::ITEM_PICK_AREA, true);
}
