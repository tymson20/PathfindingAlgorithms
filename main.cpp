#define SFML_STATIC

#include <SFML/Graphics.hpp>
#include "grid.hpp"

int main(void)
{
    const sf::Vector2f gridPosition(40.f, 40.f);
    const sf::Vector2f nodeSize(15.f, 15.f);
    const float gapWidth = 2.f;
    const unsigned int rows = 30, cols = 45;
    const sf::Color gridBackgroundColor = sf::Color(200, 200, 200);
    
    const sf::Vector2f gridSize(nodeSize.x * cols + gapWidth * (cols - 1), nodeSize.y * rows + gapWidth * (rows - 1));

    // create drawable objects
    sf::RectangleShape gridBackground(gridSize);
    gridBackground.setFillColor(gridBackgroundColor);
    gridBackground.setPosition(gridPosition);
    gridBackground.setOutlineColor(gridBackgroundColor);
    gridBackground.setOutlineThickness(5.f);

    Grid grid(gridPosition, nodeSize, gapWidth, cols, rows);

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
        }

        // clear the window with black color
        window.clear(sf::Color::Black);

        // draw everything here
        window.draw(gridBackground);
        grid.draw(window);

        // end the current frame
        window.display();
    }

    return 0;
}