#include "camera.h"
#include "object.h"

#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>
#include <memory>

void move_body(b2Body *body)
{
    const float VELOCITY = 1.0f;

    // Moving objects
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        body->SetLinearVelocity(b2Vec2(0.0f, -VELOCITY));
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        body->SetLinearVelocity(b2Vec2(0.0f, VELOCITY));
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        body->SetLinearVelocity(b2Vec2(-VELOCITY, 0.0f));
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        body->SetLinearVelocity(b2Vec2(VELOCITY, 0.0f));
    }
    if (!sf::Keyboard::isKeyPressed(sf::Keyboard::W) && !sf::Keyboard::isKeyPressed(sf::Keyboard::S) && !sf::Keyboard::isKeyPressed(sf::Keyboard::A) && !sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        body->SetLinearVelocity(b2Vec2(0.0f, 0.0f));
}

b2World world_g{b2Vec2(0.0f, 0.0f)};





int main()
{
    //      Box2D INIT
    // Creating world with gravity

    // Creating definition for bodies
    // and setting properties
    b2BodyDef wallBodyDef;
    wallBodyDef.position.Set(0.0f, -10.0f);

    b2BodyDef dynamicBodyDef;             // Body is static by default
    dynamicBodyDef.type = b2_dynamicBody; // This line makes body dynamic
    dynamicBodyDef.position.Set(0.0f, 5.0f);

    // Create body object based on its definition
    // and addin it to the world
    // b2Body *wallBody = world.CreateBody(&wallBodyDef);
    // b2Body *dynamicBody = world.CreateBody(&dynamicBodyDef);

    // Box shape
    b2PolygonShape wallBox;
    b2PolygonShape dynamicBox;
    wallBox.SetAsBox(100.0f, 10.0f);
    dynamicBox.SetAsBox(10.0f, 10.0f);
    // wallBody->SetTransform(b2Vec2(200.0f, 200.0f), 0);

    sf::RectangleShape wallShape(sf::Vector2f(100.0f, 10.0f));
    wallShape.setFillColor(sf::Color::Red);
    // Set initial position of wall
    // const b2Vec2 &currentPosition = wallBody->GetPosition();
    // wallShape.setPosition(currentPosition.x, currentPosition.y);

    // Creating fixture without definition
    // wallBody->CreateFixture(&wallBox, 0.0f);

    b2FixtureDef staticFixture;
    staticFixture.shape = &wallBox;
    staticFixture.density = 0.0f;


    // Creating fixture definition to set some properties
    b2FixtureDef dynamicFixture;
    dynamicFixture.shape = &dynamicBox;
    dynamicFixture.density = 1.0f; // For dynamic bodies it should be non-zero
    dynamicFixture.friction = 0.3f;

    // Adding fixture to a body
    // can add as many as one wishes
    // dynamicBody->CreateFixture(&dynamicFixture);

    // Simulation
    float timeStep = 1.0f / 60.0f; // Step of time between events
    int32 velocityIterations = 6;  // Velocity calculations during one step
    int32 positionIterations = 2;  // Position calculations during one step

    //      SFML
    Camera camera(1000, 1000, "Backrooms");
    sf::RectangleShape playerShape(sf::Vector2f(100.0f, 100.0f));
    playerShape.setFillColor(sf::Color::Green);
    playerShape.setOrigin(50.0f, 50.0f);
    playerShape.setPosition(0.0f, 0.0f);

    Object wall(wallShape, wallBodyDef);
    wall.addFixture(staticFixture);
    Object player(playerShape, dynamicBodyDef);
    player.addFixture(dynamicFixture);

    // Main loop
    while (camera.isOpen())
    {
        // Handling events
        camera.handleEvents();


        // Box2D step
        world_g.Step(timeStep, velocityIterations, positionIterations);
        // move_body(dynamicBody);

        // sf::Vector2f origin = playerShape.getOrigin();
        // dynamicBody->ApplyForceToCenter(b2Vec2(1.0f, 0.0f));

        // const b2Vec2 &currentPosition = dynamicBody->GetPosition();
        // playerShape.setPosition(currentPosition.x, currentPosition.y);

        player.control();

        // Drawing on screen
        camera.start();
        camera.drawOnScreen(wall);
        camera.drawOnScreen(player);
        camera.end();
    }

    return 0;
}