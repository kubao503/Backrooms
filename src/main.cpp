#include "camera.h"
#include "object3d.h"
#include "player.h"
#include "userio.h"
#include "textures.h"
#include "chunk.h"
#include "enemy.h"
#include "timer.h"
#include "item.h"
// #include "game.h"
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
    Player player(world, b2Vec2(-15.0f, -15.0f), 0);
    Enemy enemy(world, b2Vec2(-20.0f, -20.0f), 0.0f);
    Item item(world, b2Vec2(-5.0f, -15.0f), 0.0f);

    std::vector<Chunk> chunks;
    // chunks.push_back(Chunk(world, b2Vec2(20, 20)));

    for (float i = 0; i < 1000; i += 10)
        for (float j = 0; j < 1000; j += 10)
        {
            chunks.push_back(Chunk(world, b2Vec2(i, j)));
        }

    for (auto &chunk : chunks)
    {
        chunk.clear();
    }

    // for (auto &chunk : chunks)
    // {
    //     chunk.restore(world);
    // }

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

        // std::cerr << camera.getPosition().x << ' ' << camera.getPosition().y << '\n';

        // Chuncks update
        for (auto &chunk : chunks)
        {
            b2Vec2 distance = chunk.getPosition() - player.getPosition();
            if (abs(distance.x) < 50.0f && abs(distance.y) < 50.0f)
            {
                if (chunk.wasCleared())
                    chunk.restore(world);
            }
            else if (!chunk.wasCleared())
                chunk.clear();
        }

        // Drawing on screen
        Camera::drawViewOnScreen(userIO, player);
    }

    return 0;
}
