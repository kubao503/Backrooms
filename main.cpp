#include "camera.h"
#include "object.h"
#include "player.h"
#include "userio.h"
#include "myWorld.h"

UserIO userio_g(1000, 1000, "Backrooms");

int main()
{
    // Creating world without gravity
    MyWorld world{b2Vec2(0.0f, 0.0f)};

    // Definitions for bodies
    b2BodyDef staticBodyDef;
    staticBodyDef.position.Set(0.0f, 0.0f);

    b2BodyDef dynamicBodyDef;             // Body is static by default
    dynamicBodyDef.type = b2_dynamicBody; // This line makes body dynamic
    dynamicBodyDef.position.Set(0.0f, 0.0f);

    // Shapes
    b2PolygonShape wallBox;
    b2PolygonShape dynamicBox;
    wallBox.SetAsBox(100.0f, 10.0f);
    dynamicBox.SetAsBox(10.0f, 10.0f);

    // Fixtures
    b2FixtureDef staticFixture;
    staticFixture.shape = &wallBox;
    staticFixture.density = 0.0f;

    b2FixtureDef dynamicFixture;
    dynamicFixture.shape = &dynamicBox;
    dynamicFixture.density = 1.0f; // For dynamic bodies it should be non-zero
    dynamicFixture.friction = 0.3f;

    // Objects
    Player player(world, Shapes::PLAYER, dynamicBodyDef, dynamicFixture);
    Object wall(world, Shapes::WALL, staticBodyDef, staticFixture);
    Object wall2(world, Shapes::RED_WALL, staticBodyDef, staticFixture);

    // Simulation
    float timeStep = 1.0f / 60.0f; // Step of time between events
    int32 velocityIterations = 4;  // Velocity calculations during one step
    int32 positionIterations = 3;  // Position calculations during one step

    // Main loop
    while (userio_g.isOpen())
    {
        // Handling events
        userio_g.handleEvents();

        // Box2D step
        world.Step(timeStep, velocityIterations, positionIterations);
        player.control();

        // Drawing on screen
        userio_g.start();
        Camera::raycast(world, player.getPosition(), player.getAngle());
        userio_g.end();
    }

    return 0;
}