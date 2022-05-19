#include "drawableObject.h"

std::map<Object::Type, Image::Type> DrawableObject::shapesMap_{
    {Type::WALL, Image::WALL},
    {Type::RED_WALL, Image::RED_WALL},
    {Type::ENEMY, Image::ENEMY},
    {Type::EMF, Image::ENEMY}
};
