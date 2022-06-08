#define CATCH_CONFIG_MAIN
#include "catch2/catch.hpp"
#include "world.h"
#include "page.h"
#include "gameState.h"
#include "player.h"
#include "userio.h"
#include "config.h"
#include <box2d/box2d.h>

TEST_CASE("Picking up items.", "[ITEMS]")
{
    b2World world{b2Vec2(0.0f, 0.0f)};
    b2Vec2 position{0.0f, 0.0f};
    float angle = 0.0f;
    GameState game;
    Player player(world, position, angle);
    std::shared_ptr<Page> page = std::make_shared<Page>(world, position, angle, game);
    UserIO io("test");

    REQUIRE_FALSE(Page::pickedPages());

    io.setKeyPress(sf::Keyboard::Key::E);

    player.itemContact(page);
    player.control(io, Conf::timeStep);

    REQUIRE(Page::pickedPages() == 1);
}