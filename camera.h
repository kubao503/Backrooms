#ifndef CAMERA_H
#define CAMERA_H

#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>
#include <iostream>

class Object;

class Camera
{
private:
    sf::RenderWindow window_;

    // The 0, 0 coordinate coresponds to the center of the screen
    void drawOnScreen(sf::Shape &shape, float x = 0, float y = 0);

    float getRayHit(const b2RayCastInput &input);

    // Draws an object hit by a ray
    void drawRay(float angle, float distance);

public:
    Camera(unsigned int width, unsigned int height, const std::string &title)
    {
        window_.create(sf::VideoMode(width, height), title);
        getMouseXMovement();
    }
    void raycast(Object &object);
    void drawOnScreen(Object &object);
    bool isOpen() { return window_.isOpen(); }
    void handleEvents();
    void start() { window_.clear(); }
    void end() { window_.display(); }
    int getMouseXMovement();
};

#endif