#include "camera.h"
#include "object.h"
#include "player.h"
#include "userio.h"
#include "myWorld.h"

int main()
{
    // User input via mouse and output via screen
    UserIO userIO(1000, 1000, "Backrooms");

    // Creating world without gravity
    MyWorld world{b2Vec2(0.0f, 0.0f)};

    // Objects
    Player player(world, Object::PLAYER);
    Object wall(world, Object::WALL);
    Object wall2(world, Object::WALL2);

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

        // Drawing on screen
        Camera::drawViewOnScreen(userIO, world, player.getPosition(), player.getAngle());
    }

    return 0;
}