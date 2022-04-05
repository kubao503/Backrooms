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

int main()
{
    //      Box2D INIT
    // Creating world with gravity
    b2Vec2 gravity(0.0f, 0.0f);
    b2World world(gravity);

    // Creating definition for bodies
    // and setting properties
    b2BodyDef wallBodyDef;
    wallBodyDef.position.Set(0.0f, -10.0f);

    b2BodyDef dynamicBodyDef;               // Body is static by default
    dynamicBodyDef.type = b2_dynamicBody;   // This line makes body dynamic
    dynamicBodyDef.position.Set(0.0f, 5.0f);

    // Create body object based on its definition
    // and addin it to the world
    b2Body *wallBody = world.CreateBody(&wallBodyDef);
    b2Body *dynamicBody = world.CreateBody(&dynamicBodyDef);

    // Box shape
    b2PolygonShape wallBox;
    b2PolygonShape dynamicBox;
    wallBox.SetAsBox(100.0f, 10.0f);
    dynamicBox.SetAsBox(10.0f, 10.0f);
    wallBody->SetTransform(b2Vec2(200.0f, 200.0f), 0);

    sf::RectangleShape wallShape(sf::Vector2f(100.0f, 10.0f));
    wallShape.setFillColor(sf::Color::Red);
    // Set initial position of wall
    const b2Vec2& currentPosition = wallBody->GetPosition();
    wallShape.setPosition(currentPosition.x, currentPosition.y);

    // Creating fixture without definition
    wallBody->CreateFixture(&wallBox, 0.0f);

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

    //      SFML
    sf::RenderWindow window(sf::VideoMode(1000, 1000), "SFML works!");
    sf::RectangleShape playerShape(sf::Vector2f(15.0f, 15.0f));
    playerShape.setFillColor(sf::Color::Green);
    playerShape.setPosition(500.0f, 500.0f);






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

        // Box2D step
        world.Step(timeStep, velocityIterations, positionIterations);
        move_body(dynamicBody);

        sf::Vector2f origin = playerShape.getOrigin();
        // dynamicBody->ApplyForceToCenter(b2Vec2(1.0f, 0.0f));

        const b2Vec2& currentPosition = dynamicBody->GetPosition();
        playerShape.setPosition(currentPosition.x, currentPosition.y);

        // Drawing on screen
        window.clear();
        window.draw(playerShape);
        window.draw(wallShape);
        window.display();
    }

    return 0;
}