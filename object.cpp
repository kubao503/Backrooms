#include "object.h"

b2Vec2 Object::getNewPosition() const
{
    static int count{0};
    int tmp{count++};
    return b2Vec2(0, tmp * 50.0f);
}

const b2BodyDef &Object::getBodyDef(BodyType bodyType)
{
    static b2BodyDef bodyDef;
    if (bodyType == BodyType::DYNAMIC)
        bodyDef.type = b2_dynamicBody;
    else
        bodyDef.type = b2_staticBody;
    return bodyDef;
}

const b2FixtureDef &Object::getFixtureDef(const b2Vec2 &size)
{
    // Shapes
    static b2PolygonShape fixtureShape;
    fixtureShape.SetAsBox(size.x, size.y);

    // Fixtures
    static b2FixtureDef fixture;
    fixture.shape = &fixtureShape;
    fixture.density = 1.0f;

    return fixture;
}

Object::Object(MyWorld &world, Shapes::Type shapeIdx, const b2BodyDef &bodyDef, const b2FixtureDef &fixture)
    : shapeIdx_{shapeIdx}, body_{world.CreateBody(&bodyDef, *this)}
{
    body_->SetTransform(getNewPosition(), 0);
    body_->CreateFixture(&fixture);
}

Object::Object(MyWorld &world, Shapes::Type shapeIdx, BodyType bodyType, const b2Vec2 &size)
    : Object(world, shapeIdx, getBodyDef(bodyType), getFixtureDef(size)) {}

Object Object::objectGenerator(MyWorld &world, ObjectType objectType)
{
    static constexpr Shapes::Type shapeIdx[ObjectType::TOTAL]{
        Shapes::WALL, Shapes::RED_WALL, Shapes::PLAYER};
    static constexpr BodyType bodyTypes[ObjectType::TOTAL]{
        BodyType::STATIC, BodyType::STATIC, BodyType::DYNAMIC};
    static const b2Vec2 sizes[ObjectType::TOTAL]{
        b2Vec2(100.0f, 10.0f), b2Vec2(100.0f, 10.0f), b2Vec2(10.0f, 10.0f)};
    return Object(world, shapeIdx[objectType], bodyTypes[objectType], sizes[objectType]);
}