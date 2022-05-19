#include "gameState.h"

GameState::GameState()
    : listener_{*this, debugMode_},
      player_{world_, {0.f, 0.f}, 0.f},
      enemy_{world_, {Conf::chunkWidth, 0.f}, 0.f}
{
    // Setting contact listener
    world_.SetContactListener(&listener_);
}

void GameState::addObject(std::shared_ptr<Object> object)
{
    assert(object); // check if object is not nullptr

    objects_.insert(object);
}

void GameState::debugUpdate(UserIO &userIO)
{
    // Toggle debug mode
    if (userIO.handleKeyPress(sf::Keyboard::Slash))
        debugSet(!debugGet());
}

void GameState::huntUpdate()
{
    if (gameMap_.isHunt(player_.getPosition()))
        enemy_.startHunt(world_, player_);
}

void GameState::notify(const Component &comp, Event event)
{
    // handling notifications
    switch (event)
    {
    case Mediator::ITEM_CONTACT:
        player_.itemContact(shareObject(static_cast<const Item *>(&comp)));
        break;
    case Mediator::GAMEOVER:
        gameOver();
        break;
    default:
        throw "Event impossible to handle";
    }
}

void GameState::notify(std::shared_ptr<Component> comp, Event event)
{
    switch (event)
    {
    case Mediator::ITEM_CREATED:
        addObject(std::static_pointer_cast<Item>(comp));
        break;
    default:
        throw "Event impossible to handle";
    }
}

void GameState::gameOver()
{
    isOver_ = true;
}

void GameState::step(UserIO &userIO)
{
    // Drawing on screen
    Camera::drawViewOnScreen(userIO, debugGet(), player_);
    world_.Step(Conf::timeStep, Conf::velocityIterations, Conf::positionIterations);

    // Jumpscare
    if (isOver_)
    {
        player_.stop();
        enemy_.stop();
        player_.lookAt(enemy_.getPosition());
        return;
    }

    // Physics step
    gameMap_.draw(world_, player_.getPosition(), *this);

    player_.control(userIO);
    player_.doItemAction();
    enemy_.control(player_.getPosition(), gameMap_, debugGet());

    debugUpdate(userIO);
    huntUpdate();

    // DEBUG
    // int counter = 0;
    // for (auto obj : player_.getOwnedItems())
    //     std::cerr << ++counter << ' ' << obj.use_count() << '\n';
}
