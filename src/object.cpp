#include "object.h"

Object::Arguments::Arguments(b2BodyType bodyType, const b2Shape &shape)
    : bodyType_{bodyType}, fixDef_{getFixtureDef(shape)} {}

Object::Arguments Object::argList[ObjectType::TOTAL]{
    {b2_staticBody, getShape(6.0f, 1.0f)},
    {b2_staticBody, getShape(6.0f, 1.0f)},
    {b2_dynamicBody, getShape(0.5f)},
    {b2_dynamicBody, getShape(0.5f)},
    {b2_staticBody, getShape(1.0f)},
    {b2_staticBody, getShape(Conf::FOVangle, Conf::renderDistance, 5)}};

b2Vec2 Object::getNewPosition() const
{
    static int count{0};
    int tmp{count++};
    return b2Vec2(0, tmp * 50.0f);
}

const b2BodyDef &Object::getBodyDef(b2BodyType bodyType)
{
    static b2BodyDef bodyDef;
    bodyDef.type = bodyType;
    return bodyDef;
}

const b2Shape &Object::getShape(float halfX, float halfY)
{
    static b2PolygonShape shape; // Shape
    shape.SetAsBox(halfX, halfY);
    return shape;
}

const b2Shape &Object::getShape(float radius)
{
    static b2CircleShape shape; // Shape
    shape.m_radius = radius;
    return shape;
}

const b2Shape &Object::getShape(float FOVangle, float renderDist, int verticesCount)
{
    auto vertices = std::make_unique<b2Vec2[]>(verticesCount); // {new b2Vec2[verticesCount]{{0, 0}}};
    for (int i{1}; i < verticesCount; ++i)
    {
        float angle{FOVangle / (verticesCount - 2) * (2 * i - verticesCount)};
        vertices[i] = renderDist * getVecN(angle);
    }

    static b2PolygonShape shape;
    shape.Set(vertices.get(), verticesCount);

    return shape;
}

const b2FixtureDef &Object::getFixtureDef(const b2Shape &shape)
{
    static b2FixtureDef fixture; // Fixture
    fixture.shape = &shape;
    fixture.density = 1.0f;
    fixture.friction = 0.0f;
    return fixture;
}

// const std::function<const b2FixtureDef *()> Object::fixtureCalls[ObjectType::TOTAL]{
//     []()
//     { return getFixtureDef(b2Vec2(6.0f, 1.0f)); },
//     []()
//     { return getFixtureDef(b2Vec2(6.0f, 1.0f)); },
//     []()
//     { return getFixtureDef(0.5f); },
//     []()
//     { return getFixtureDef(0.5f); },
//     []()
//     { return getFixtureDef(1.0f); }};

Object::Object(b2World &world, ObjectType type)
    : Object{world, type, getNewPosition(), 0} {}

Object::Object(b2World &world, ObjectType type, const b2Vec2 &position, float angle)
{
    setBody(world, type, position, angle);
}

void Object::setBody(b2World &world, ObjectType type, const b2Vec2 &position, float angle)
{
    body_ = std::unique_ptr<b2Body>(world.CreateBody(&getBodyDef(argList[type].bodyType_)));
    body_->SetTransform(position, angle);
    body_->CreateFixture(&argList[type].fixDef_);

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
