#include "camera.h"
#include "object.h"

#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>
#include <memory>

// Creating world without gravity
b2World world_g{b2Vec2(0.0f, 0.0f)};

int main()
{
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

    //      SFML
    Camera camera(1000, 1000, "Backrooms");

    sf::RectangleShape playerShape(sf::Vector2f(10.0f, 10.0f));
    playerShape.setFillColor(sf::Color::Green);
    // playerShape.setOrigin(5.0f, 5.0f);

    sf::RectangleShape wallShape(sf::Vector2f(100.0f, 10.0f));
    wallShape.setFillColor(sf::Color::Red);
    // wallShape.setOrigin(50.0f, 5.0f);

    // Objects
    Object wall(wallShape, staticBodyDef);
    Object wall2(wallShape, staticBodyDef);
    Object player(playerShape, dynamicBodyDef);

    // Fixtures
    wall.addFixture(staticFixture);
    wall2.addFixture(staticFixture);
    player.addFixture(dynamicFixture);

    // Simulation
    float timeStep = 1.0f / 60.0f; // Step of time between events
    int32 velocityIterations = 6;  // Velocity calculations during one step
    int32 positionIterations = 2;  // Position calculations during one step

    // Main loop
    while (camera.isOpen())
    {
        // Handling events
        camera.handleEvents();

        // Box2D step
        world_g.Step(timeStep, velocityIterations, positionIterations);
        player.control();

        // Drawing on screen
        camera.start();
        camera.drawOnScreen(wall);
        camera.drawOnScreen(wall2);
        camera.drawOnScreen(player);
        camera.end();
    }

    return 0;
}