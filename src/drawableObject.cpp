#include "drawableObject.h"

std::map<Object::Type, Shapes::Type> DrawableObject::shapesMap_{
    {Type::WALL, Shapes::WALL},
    {Type::RED_WALL, Shapes::RED_WALL},
    {Type::ENEMY, Shapes::ENEMY},
    {Type::ITEM, Shapes::ENEMY}
};
