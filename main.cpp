#define SFML_STATIC

#include <iostream>
#include <SFML/Graphics.hpp>
#include "backend.hpp"
#include "legendBar.hpp"
#include "settingsBar.hpp"
#include "buttonsBar.hpp"

int main(void)
{
    int fpsCounter = 0;
    sf::Clock clock;
    const sf::Vector2f gridPosition(20.f, 20.f);
    const sf::Vector2f nodeSize(15.f, 15.f);
    const float gapWidth = 2.f;
    const unsigned int rows = 30, cols = 40;
    const sf::Color gridBackgroundColor = sf::Color(200, 200, 200);
    sf::Font font;
    font.loadFromFile("../Minecraft.ttf");
    
    // create drawable objects

    sf::Text GUIName("Pathfinding\nalgorithms", font, 43U);
    GUIName.setPosition(sf::Vector2f(730.f, 20.f));

    sf::Text fpsText = sf::Text("0 fps", font, 10U);
    fpsText.setFillColor(sf::Color::Green);

    Grid grid(gridPosition, nodeSize, gapWidth, rows, cols, gridBackgroundColor, gridBackgroundColor);
    LegendBar legendBar(sf::Vector2f(20.f, 550.f), sf::Vector2f(700.f, 40.f), font);
    SettingsBar settingsBar(sf::Vector2f(740.f, 130.f), sf::Vector2f(200.f, 200.f), font);
    ButtonsBar buttonsBar(sf::Vector2f(750.f, 400.f), sf::Vector2f(200.f, 175.f), font);
    Backend backend(&grid, &legendBar, &settingsBar, &buttonsBar);

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
                    backend.leftMouseButtonPressed({event.mouseButton.x, event.mouseButton.y});
                else if (event.mouseButton.button == sf::Mouse::Right)
                    backend.rightMouseButtonPressed({event.mouseButton.x, event.mouseButton.y});
            }
            else if (event.type == sf::Event::MouseButtonReleased)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                    backend.leftMouseButtonReleased();
                else if (event.mouseButton.button == sf::Mouse::Right)
                    backend.rightMouseButtonReleased();
            }
        }

        if (clock.getElapsedTime().asMilliseconds() >= 1000)
        {
            fpsText.setString(std::to_string(fpsCounter) + " fps");
            clock.restart();
            fpsCounter = 0;
        }
        else
            fpsCounter += 1;
        
        backend.update(window);

        // clear the window with black color
        window.clear(sf::Color::Black);

        // draw everything here
        window.draw(fpsText);
        grid.draw(window);
        legendBar.draw(window);
        settingsBar.draw(window);
        buttonsBar.draw(window);
        window.draw(GUIName);

        // end the current frame
        window.display();
    }

    return 0;
}