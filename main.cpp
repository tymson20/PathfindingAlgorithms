#define SFML_STATIC

#include <iostream>
#include <SFML/Graphics.hpp>
#include "backend.hpp"

int main(void)
{
    const sf::Vector2f gridPosition(40.f, 40.f);
    const sf::Vector2f nodeSize(15.f, 15.f);
    const float gapWidth = 2.f;
    const unsigned int rows = 30, cols = 45;
    const sf::Color gridBackgroundColor = sf::Color(200, 200, 200);
    
    // create drawable objects

    Grid grid(gridPosition, nodeSize, gapWidth, rows, cols, gridBackgroundColor, gridBackgroundColor);
    Backend backend(&grid);

    // create the window
    sf::RenderWindow window(sf::VideoMode(1000, 600), "Pathfinding Algorithms", sf::Style::Titlebar | sf::Style::Close);

    // run the program as long as the window is open
    while (window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();
            else if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                    backend.leftMouseButtonCliked({event.mouseButton.x, event.mouseButton.y});
                else if (event.mouseButton.button == sf::Mouse::Right)
                    backend.rightMouseButtonCliked({event.mouseButton.x, event.mouseButton.y});
            }
        }

        // clear the window with black color
        window.clear(sf::Color::Black);

        // draw everything here
        grid.draw(window);

        // end the current frame
        window.display();
    }

    return 0;
}