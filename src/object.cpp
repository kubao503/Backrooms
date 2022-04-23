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
    static b2PolygonShape rectShape; // Shape
    rectShape.SetAsBox(size.x, size.y);

    static b2FixtureDef fixture; // Fixture
    fixture.shape = &rectShape;
    fixture.density = 1.0f;
    fixture.friction = 0.0f;
    return fixture;
}

const b2FixtureDef &Object::getFixtureDef(float radius)
{
    static b2CircleShape circleShape; // Shape
    circleShape.m_radius = radius;

    static b2FixtureDef fixture; // Fixture
    fixture.shape = &circleShape;
    fixture.density = 1.0f;
    fixture.friction = 0.0f;
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
    static const std::function<b2FixtureDef()> fixtureCalls[ObjectType::TOTAL]{
        []()
        { return getFixtureDef(b2Vec2(100.0f, 10.0f)); },
        []()
        { return getFixtureDef(b2Vec2(100.0f, 10.0f)); },
        []()
        { return getFixtureDef(10.0f); }};

    static constexpr Shapes::Type shapeIdx[ObjectType::TOTAL]{
        Shapes::WALL, Shapes::RED_WALL, Shapes::PLAYER};

    static constexpr BodyType bodyTypes[ObjectType::TOTAL]{
        BodyType::STATIC, BodyType::STATIC, BodyType::DYNAMIC};

    return Object(world, shapeIdx[objectType], getBodyDef(bodyTypes[objectType]), fixtureCalls[objectType]());
}