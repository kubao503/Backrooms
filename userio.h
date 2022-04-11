#ifndef USER_IO_H
#define USER_IO_H

#include "object.h"

#include <SFML/Graphics.hpp>

class UserIO
{
private:
    sf::RenderWindow window_;

public:
    UserIO(unsigned int width, unsigned int height, const std::string &title)
    {
        getMouseXMovement();
        window_.create(sf::VideoMode(width, height), title);
    }

    // The 0, 0 coordinate coresponds to the center of the screen
    void drawOnScreen(Shapes::Type shapeIdx, float x = 0, float y = 0, float xScale = 1.0f, float yScale = 1.0f);
    void drawObject(Object &object);

    bool isOpen() { return window_.isOpen(); }
    void start() { window_.clear(); }
    void end() { window_.display(); }
    void handleEvents();
    int getMouseXMovement();
};

#endif