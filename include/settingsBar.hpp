#ifndef SETTINGSBAR_HPP
#define SETTINGSBAR_HPP

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>

enum class Algorithm {Dijkstra, Astar};

struct AlgorithmElement {
    Algorithm algorithm;
    sf::RectangleShape rectangleShape;
    sf::Text text;
};

class SettingsBar
{
public:
    SettingsBar(const sf::Vector2f& position, const sf::Vector2f& size, const sf::Font& font);

    Algorithm update(const sf::Vector2f& cursorPosition);

    void draw(sf::RenderWindow& renderWindow) const;

    sf::FloatRect getGlobalBounds() const { return sf::FloatRect(m_Position, m_Size); }

private:
    const sf::Vector2f m_Position;
    const sf::Vector2f m_Size;
    AlgorithmElement* m_CurrentAlgorithm;
    AlgorithmElement algorithms[2];
};

#endif // SETTINGSBAR_HPP