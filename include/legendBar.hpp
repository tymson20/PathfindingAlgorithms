#ifndef LEGENDBAR_HPP
#define LEGENDBAR_HPP

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include "node.hpp"

struct LegendElement
{
    Node::Type type;
    sf::RectangleShape rectangleShape;
    sf::Text text;
};

class LegendBar
{
private:
    static const Node::Type types[5];
    static const sf::Color colors[5];
    static const sf::String labels[5];
public:
    LegendBar(const sf::Vector2f& position, const sf::Vector2f& size, const sf::Font& font);

    Node::Type update(const sf::Vector2f& cursorPosition);

    void draw(sf::RenderWindow& renderWindow) const;

    sf::FloatRect getGlobalBounds() const { return sf::FloatRect(m_Position, m_Size); }

private:
    const sf::Vector2f m_Position;
    const sf::Vector2f m_Size;
    LegendElement elements[5];
    LegendElement* m_HighlightedElement;
};

#endif // LEGENDBAR_HPP