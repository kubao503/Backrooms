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
    else if (bodyType == BodyType::STATIC)
        bodyDef.type = b2_staticBody;
    else
        throw "Invalid body type\n";
    return bodyDef;
}

const b2FixtureDef *Object::getFixtureDef(const b2Vec2 &size)
{
    static b2PolygonShape rectShape; // Shape
    rectShape.SetAsBox(size.x, size.y);

    static b2FixtureDef fixture; // Fixture
    fixture.shape = &rectShape;
    fixture.density = 1.0f;
    fixture.friction = 0.0f;
    return &fixture;
}

const b2FixtureDef *Object::getFixtureDef(float radius)
{
    static b2CircleShape circleShape; // Shape
    circleShape.m_radius = radius;

    static b2FixtureDef fixture; // Fixture
    fixture.shape = &circleShape;
    fixture.density = 1.0f;
    fixture.friction = 0.0f;
    return &fixture;
}

const std::function<const b2FixtureDef *()> Object::fixtureCalls[ObjectType::TOTAL]{
    []()
    { return getFixtureDef(b2Vec2(6.0f, 1.0f)); },
    []()
    { return getFixtureDef(b2Vec2(6.0f, 1.0f)); },
    []()
    { return getFixtureDef(0.5f); },
    []()
    { return getFixtureDef(0.5f); },
    []()
    { return getFixtureDef(1.0f); }};

Object::Object(b2World &world, ObjectType type)
    : Object{world, type, getNewPosition(), 0} {}

Object::Object(b2World &world, ObjectType type, const b2Vec2 &position, float angle)
    : shapeIdx_{shapeIdx[type]}
{
    setBody(world, type, position, angle);
}

void Object::setBody(b2World &world, ObjectType type, const b2Vec2 &position, float angle)
{
    body_ = std::unique_ptr<b2Body>(world.CreateBody(&getBodyDef(bodyTypes[type])));
    body_->SetTransform(position, angle);
    body_->CreateFixture(fixtureCalls[type]());

    // Setting Object as user data
    body_->GetUserData().pointer = (uintptr_t)this;
}

void Object::destroyBody()
{
    body_->GetWorld()->DestroyBody(body_.get());
    body_.release(); // This body is no longer valid
}

void Object::setSensor(bool sensor)
{
    body_->GetFixtureList()[0].SetSensor(sensor);
}
