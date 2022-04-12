#include "object.h"

b2Vec2 Object::getNewPosition()
{
    static int count{0};
    int tmp{count++};
    return b2Vec2(0, tmp * 50.0f);
}

Object::Object(MyWorld &world, Shapes::Type shapeIdx, const b2BodyDef &bodyDef, const b2FixtureDef &fixture)
    : shapeIdx_{shapeIdx}
{
    body_ = world.CreateBody(&bodyDef, *this);
    body_->SetTransform(getNewPosition(), 0);
    this->addFixture(fixture);
}
