#include "game.h"

void Game::createItem(b2World &world, Object::Type type, const b2Vec2 &position, float angle)
{
    if (type == Object::Type::EMF)
    objects_.emplace(std::make_shared<Emf>(world, position, angle));
}
