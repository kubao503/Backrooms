#ifndef DRAWABLE_OBJECT_H
#define DRAWABLE_OBJECT_H

#include "object.h"
#include "shapes.h" // for shapeIdx_ attribute

#include <map>

class DrawableObject : public Object
{
private:
    const Shapes::Type shapeIdx_;
    static std::map<Object::ObjectType, Shapes::Type> shapesMap_;
    
protected:
    DrawableObject(b2World &world, ObjectType type, const b2Vec2 &position, float angle)
        : Object{world, type, position, angle}, shapeIdx_{shapesMap_.at(type)} {}

public:
    Shapes::Type getShapeIdx() const { return shapeIdx_; }
};

#endif
