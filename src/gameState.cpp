#include "gameState.h"

GameState::GameState()
    : listener_{*this},
      player_{world_, {0.f, 0.f}, 0.f},
      enemy_{world_, {Conf::chunkWidth, 0.f}, 0.f}
{
    // Setting contact listener
    world_.SetContactListener(&listener_);

    addObject(std::make_shared<Emf>(world_, b2Vec2(0.0f, -10.0f), 0.0f, enemy_));
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
    gameMap_.draw(world_, player_.getPosition());

    player_.control(userIO);
    player_.doItemAction();
    enemy_.control(player_.getPosition(), gameMap_, debugGet());

    debugUpdate(userIO);

}
