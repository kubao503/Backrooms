#include "object.h"

const std::map<Object::Category, uint16> Object::collisionMask_{
    {DEFAULT, 0xFFFF},
    {WALL, PLAYER | OBJECT2D},
    {PLAYER, WALL | PLAYER | OBJECT2D},
    {CAMERA, OBJECT2D},
    {OBJECT2D, WALL | PLAYER | CAMERA | OBJECT2D}};

const std::map<Object::Type, Object::Category> Object::categoryMap_{
    {Type::WALL, WALL},
    {Type::RED_WALL, WALL},
    {Type::PLAYER, PLAYER},
    {Type::ENEMY, OBJECT2D},
    {Type::ITEM, OBJECT2D},
    {Type::CAMERA, CAMERA}
};

const Object::Arguments Object::argList[static_cast<int>(Type::TOTAL)]{
    {b2_staticBody, getShape(6.0f, 1.0f)},
    {b2_staticBody, getShape(6.0f, 1.0f)},
    {b2_dynamicBody, getShape(0.5f)},
    {b2_dynamicBody, getShape(0.5f)},
    {b2_staticBody, getShape(1.0f)},
    {b2_staticBody, getShape(Conf::FOVangle, Conf::renderDistance, 5)}};

Object::Arguments::Arguments(b2BodyType bodyType, const b2Shape &shape)
    : bodyType_{bodyType}, fixDef_{getFixtureDef(shape)} {}

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
    bodyDef.position.SetZero();
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
        float angle{FOVangle / 2.0f / (verticesCount - 2) * (2 * i - verticesCount)};
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

Object::Object(b2World &world, Type type)
    : Object{world, type, getNewPosition(), 0} {}

Object::Object(b2World &world, Type type, const b2Vec2 &position, float angle)
{
    setBody(world, type, position, angle);
}

void Object::setBody(b2World &world, Type type, const b2Vec2 &position, float angle)
{
    int argIdx{static_cast<int>(type)};
    body_ = std::unique_ptr<b2Body>(world.CreateBody(&getBodyDef(argList[argIdx].bodyType_)));
    body_->SetTransform(position, angle);
    body_->CreateFixture(&argList[argIdx].fixDef_);

    // Setting proper collision filter
    setCollisionFilter(categoryMap_.at(type));

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
    body_->GetFixtureList()->SetSensor(sensor);
}

void Object::setCollisionFilter(Category category) const
{
    b2Filter filter;
    filter.categoryBits = static_cast<uint16>(category);
    filter.maskBits = collisionMask_.at(category);
    body_->GetFixtureList()->SetFilterData(filter);
}
