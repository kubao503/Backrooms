#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>
#include <memory>

void move_shape(sf::Shape &shape)
{
    const float VELOCITY = 0.5f;

        // Moving objects
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        shape.move(0.0f, -VELOCITY);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        shape.move(0.0f, VELOCITY);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        shape.move(-VELOCITY, 0.0f);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        shape.move(VELOCITY, 0.0f);
    }
}

int main()
{
    //      Box2D INIT
    // Creating world with gravity
    b2Vec2 gravity(0.0f, -10.0f);
    b2World world(gravity);

    // Creating definition for bodies
    // and setting properties
    b2BodyDef groundBodyDef;
    groundBodyDef.position.Set(0.0f, -10.0f);

    b2BodyDef dynamicBodyDef;               // Body is static by default
    dynamicBodyDef.type = b2_dynamicBody;   // This line makes body dynamic
    dynamicBodyDef.position.Set(0.0f, 5.0f);

    // Create body object based on its definition
    // and addin it to the world
    b2Body *groundBody = world.CreateBody(&groundBodyDef);
    b2Body *dynamicBody = world.CreateBody(&dynamicBodyDef);

    // Box shape
    b2PolygonShape groundBox;
    b2PolygonShape dynamicBox;
    groundBox.SetAsBox(50.0f, 10.0f);
    dynamicBox.SetAsBox(1.0f, 1.0f);

    // Creating fixture without definition
    groundBody->CreateFixture(&groundBox, 0.0f);

    // Creating fixture definition to set some properties
    b2FixtureDef dynamicFixture;
    dynamicFixture.shape = &dynamicBox;
    dynamicFixture.density = 1.0f;      // For dynamic bodies it should be non-zero
    dynamicFixture.friction = 0.3f;

    // Adding fixture to a body
    // can add as many as one wishes
    dynamicBody->CreateFixture(&dynamicFixture);

    // Simulation
    float timeStep = 1.0f / 60.0f;  // Step of time between events
    int32 velocityIterations = 6;   // Velocity calculations during one step
    int32 positionIterations = 2;   // Position calculations during one step

    // for (int32 i = 0; i < 60; ++i)
    // {
    //     world.Step(timeStep, velocityIterations, positionIterations);
    //     b2Vec2 position = dynamicBody->GetPosition();
    //     float angle = dynamicBody->GetAngle();
    //     printf("%4.2f %4.2f %4.2f\n", position.x, position.y, angle);
    // }

    //      SFML
    sf::RenderWindow window(sf::VideoMode(1000, 1000), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);
    shape.setPosition(500.0f, 500.0f);

    // Main loop
    while (window.isOpen())
    {
        // Handling events
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        move_shape(shape);

        // Drawing on screen
        window.clear();
        window.draw(shape);
        window.display();
    }




    return 0;
}