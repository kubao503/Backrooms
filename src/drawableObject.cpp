#include "drawableObject.h"

std::map<Object::ObjectType, Shapes::Type> DrawableObject::shapesMap_{
    {Object::WALL, Shapes::WALL},
    {Object::RED_WALL, Shapes::RED_WALL},
    {Object::ENEMY, Shapes::ENEMY},
    {Object::ITEM, Shapes::ENEMY}
};
