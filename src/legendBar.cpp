#define SFML_STATIC

#include <algorithm>
#include "legendBar.hpp"

const Node::Type LegendBar::types[5] = {Node::Type::Barrier,
                                     Node::Type::Start,
                                     Node::Type::End,
                                     Node::Type::Path,
                                     Node::Type::Visited};

const sf::Color LegendBar::colors[5] = {sf::Color(50, 50, 50),
                                        sf::Color::Red,
                                        sf::Color(0, 227, 13),
                                        sf::Color(0, 93, 199),
                                        sf::Color(110, 175, 250)};

const sf::String LegendBar::labels[5] = {"Barrier",
                                         "Start",
                                         "End",
                                         "Path",
                                         "Visited"};

LegendBar::LegendBar(const sf::Vector2f& position, const sf::Vector2f& size, const sf::Font& font)
    : m_Position(position), m_Size(size), m_HighlightedElement(elements)
{
    constexpr int divider = 5 * 5;
    const float nodeX = size.x / (float)divider;
    const float nodeSize = std::min(nodeX, size.y);
    float posX = position.x;
    for (int i = 0; i < 5; i++)
    {
        elements[i].type = types[i];
        elements[i].rectangleShape = sf::RectangleShape({nodeSize, nodeSize});
        elements[i].rectangleShape.setPosition({posX, position.y});
        elements[i].rectangleShape.setFillColor(colors[i]);
        elements[i].rectangleShape.setOutlineColor(sf::Color::White);
        posX += 1.5f * nodeX;
        elements[i].text = sf::Text(labels[i], font, 25U);
        elements[i].text.setPosition({posX, position.y});
        posX += 3.5f * nodeX;
    }
    m_HighlightedElement->rectangleShape.setOutlineThickness(3.f);
}

Node::Type LegendBar::update(const sf::Vector2f& cursorPosition)
{
    for (int i = 0; i < 3; i++)
    {
        if (elements[i].rectangleShape.getGlobalBounds().contains(cursorPosition))
        {
            m_HighlightedElement->rectangleShape.setOutlineThickness(0.f);
            m_HighlightedElement = elements+i;
            m_HighlightedElement->rectangleShape.setOutlineThickness(3.f);
            return elements[i].type;
        }
    }
    return Node::Type::Empty;
}

void LegendBar::draw(sf::RenderWindow& renderWindow) const
{
    for (int i = 0; i < 5; i++)
    {
        renderWindow.draw(elements[i].rectangleShape);
        renderWindow.draw(elements[i].text);
    }
}