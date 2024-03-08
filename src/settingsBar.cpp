#define SFML_STATIC

#include "settingsBar.hpp"

SettingsBar::SettingsBar(const sf::Vector2f& position, const sf::Vector2f& size, const sf::Font& font)
    : m_Position(position), m_Size(size), m_CurrentAlgorithm(algorithms)
{
    sf::Vector2f rectangleSize(15.f, 15.f);
    algorithms[0].algorithm = Algorithm::Dijkstra;
    algorithms[0].rectangleShape = sf::RectangleShape(rectangleSize);
    algorithms[0].rectangleShape.setPosition(sf::Vector2f(position.x, position.y + 15.f));
    algorithms[0].rectangleShape.setFillColor(sf::Color::White);
    algorithms[0].rectangleShape.setOutlineColor(sf::Color::White);
    algorithms[0].rectangleShape.setOutlineThickness(2.f);
    algorithms[0].text = sf::Text("Dijkstra", font, 34);
    algorithms[0].text.setPosition(sf::Vector2f(position.x + size.x / 4, position.y));
    algorithms[1].algorithm = Algorithm::Astar;
    algorithms[1].rectangleShape = sf::RectangleShape(rectangleSize);
    algorithms[1].rectangleShape.setPosition(sf::Vector2f(position.x, position.y + size.y / 4 + 15.f));
    algorithms[1].text = sf::Text("A star", font, 34);
    algorithms[1].text.setPosition(sf::Vector2f(position.x + size.x / 4, position.y + size.y / 4));
    algorithms[1].rectangleShape.setFillColor(sf::Color::Black);
    algorithms[1].rectangleShape.setOutlineColor(sf::Color::White);
    algorithms[1].rectangleShape.setOutlineThickness(2.f);

    m_Diagonal= sf::Text("Diagonal", font);
    m_Diagonal.setPosition(sf::Vector2f(739.f, 230.f));
    m_Diagonal.setFillColor(sf::Color::White);
}

std::pair<Algorithm, bool> SettingsBar::update(const sf::Vector2f& cursorPosition)
{
    for (int i = 0; i < 2; i++)
    {
        if (algorithms[i].rectangleShape.getGlobalBounds().contains(cursorPosition))
        {
            m_CurrentAlgorithm->rectangleShape.setFillColor(sf::Color::Black);
            m_CurrentAlgorithm = algorithms+i;
            m_CurrentAlgorithm->rectangleShape.setFillColor(sf::Color::White);
            break;
        }
    }
    if (m_Diagonal.getGlobalBounds().contains(cursorPosition))
    {
        if (m_Diagonal.getStyle() == sf::Text::Style::Regular)
            m_Diagonal.setStyle(sf::Text::Style::Underlined);
        else
            m_Diagonal.setStyle(sf::Text::Style::Regular);
    }
    return std::make_pair(m_CurrentAlgorithm->algorithm, m_Diagonal.getStyle() == sf::Text::Style::Underlined);
}

void SettingsBar::draw(sf::RenderWindow& renderWindow) const
{
    for (int i = 0; i < 2; i++)
    {
        renderWindow.draw(algorithms[i].rectangleShape);
        renderWindow.draw(algorithms[i].text);
    }
    renderWindow.draw(m_Diagonal);
}