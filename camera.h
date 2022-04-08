#ifndef CAMERA_H
#define CAMERA_H

#include <SFML/Graphics.hpp>
#include <iostream>

class Object;

class Camera
{
private:
    sf::RenderWindow window_;

    // The 0, 0 coordinate coresponds to the center of the screen
    void drawOnScreen(sf::Shape &shape, float x = 0, float y = 0)
    {
        sf::Vector2u size{window_.getSize()};
        shape.setPosition(x + size.x / 2.0f, y + size.y / 2.0f);
        window_.draw(shape);
    }

public:
    Camera(unsigned int width, unsigned int height, const std::string &title)
    {
        window_.create(sf::VideoMode(width, height), title);
    }

    void drawOnScreen(Object &object);
    bool isOpen() { return window_.isOpen(); }
    void handleEvents();
    void start() { window_.clear(); }
    void end() { window_.display(); }
};

#endif