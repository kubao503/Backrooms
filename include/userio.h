#ifndef USER_IO_H
#define USER_IO_H

#include <SFML/Graphics.hpp> // for using sf::RenderWindow
#include "shapes.h"          // for drawing sf::Shape
#include <memory>            // for moving sf::Color
#include <algorithm>         // for std::min

// #include <iostream>

class UserIO
{
private:
    sf::RenderWindow window_;
    bool focus_{true}; // Focus on game window

    sf::Color dimColor(const sf::Color &color, float dimFactor);
    void setScale(sf::Shape &shape);

public:
    UserIO(unsigned int width, unsigned int height, const std::string &title)
    {
        getMouseXMovement();
        window_.create(sf::VideoMode(width, height), title);
    }

    // The 0, 0 coordinate coresponds to the center of the screen
    void drawOnScreen(Shapes::Type shapeIdx, float x = 0, float y = 0, float xScale = 1.0f, float yScale = 1.0f, float dim = 1.0f);

    bool isOpen() { return window_.isOpen(); }
    // Starts making new frame
    void start() { window_.clear(); }
    // Displays frame
    void end() { window_.display(); }
    void handleEvents();
    int getMouseXMovement();
};

#endif
