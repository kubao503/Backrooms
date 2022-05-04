#include "camera.h"
#include "object3d.h"
#include "player.h"
#include "userio.h"
#include "textures.h"
#include "chunk.h"
#include "enemy.h"
#include "timer.h"
#include "world.h"
#include "myListener.h" // for setting contact listener

#include <vector>   // TEST
#include <iostream> // Printing information about texture loading fail

int main()
{
    // Loading textures
    if (!Textures::init())
    {
        std::cerr << "Loading textures failed\n";
    }
    Shapes::init();

    // User input via mouse and output via screen
    UserIO userIO(1600, 900, "Backrooms");

    // Creating world without gravity
    b2World world{b2Vec2(0.0f, 0.0f)};

    // Setting contact listener
    MyListener listener;
    world.SetContactListener(&listener);

    // Objects
    Player player(world, Object::PLAYER, b2Vec2(0.0f, -20.0f), 0);
    Enemy enemy(world, Object::ENEMY, b2Vec2(-20.0f, -30.0f), 0);

    // Creating chunks
    World gameWorld(world, 100);

    // Simulation parameters
    float timeStep = 1.0f / 60.0f; // Step of time between events
    int32 velocityIterations = 4;  // Velocity calculations during one step
    int32 positionIterations = 3;  // Position calculations during one step

    // Main loop
    while (userIO.isOpen())
    {
        // Handling events
        userIO.handleEvents();

        // Physics step
        world.Step(timeStep, velocityIterations, positionIterations);
        player.control(userIO);
        // enemy.control(player);

        // Chunks update
        gameWorld.draw(world, player);

        b2Vec2 closestChunk = gameWorld.closestChunk(player);
        std::cout << closestChunk.x << " " << closestChunk.y << std::endl; // DEBUG

        // Drawing on screen
        Camera::drawViewOnScreen(userIO, world, player, enemy);
    }

    return 0;
}
