#define SFML_STATIC

#include "buttonsBar.hpp"

ButtonsBar::ButtonsBar(const sf::Vector2f& position, const sf::Vector2f& size, const sf::Font& font)
    : m_Position(position), m_Size(size)
{
    m_StartButton.rectangleShape = sf::RectangleShape(sf::Vector2f(size.x, 50.f));
    m_StartButton.rectangleShape.setPosition(position);
    m_StartButton.rectangleShape.setFillColor(sf::Color::White);
    m_StartButton.text = sf::Text("Start", font, 40U);
    m_StartButton.text.setStyle(sf::Text::Style::Bold);
    m_StartButton.text.setPosition(position + sf::Vector2f(50.f, 0.f));
    m_StartButton.text.setFillColor(sf::Color::Black);

    const sf::Vector2f clearButtonPosition(position + sf::Vector2f(25.f, 75.f));
    m_ClearButton.rectangleShape = sf::RectangleShape(sf::Vector2f(150.f, 40.f));
    m_ClearButton.rectangleShape.setPosition(clearButtonPosition);
    m_ClearButton.rectangleShape.setFillColor(sf::Color::White);
    m_ClearButton.text = sf::Text("Clear", font);
    m_ClearButton.text.setStyle(sf::Text::Style::Bold);
    m_ClearButton.text.setPosition(clearButtonPosition + sf::Vector2f(35.f, 2.f));
    m_ClearButton.text.setFillColor(sf::Color::Black);
}

ButtonsBar::ButtonType ButtonsBar::update(const sf::Vector2f& cursorPosition)
{
    if (m_StartButton.rectangleShape.getGlobalBounds().contains(cursorPosition))
        return ButtonType::Start;
    else if (m_ClearButton.rectangleShape.getGlobalBounds().contains(cursorPosition))
        return ButtonType::Clear;
    return ButtonType::None;
}

void ButtonsBar::draw(sf::RenderWindow& renderWindow) const
{
    renderWindow.draw(m_StartButton.rectangleShape);
    renderWindow.draw(m_StartButton.text);
    renderWindow.draw(m_ClearButton.rectangleShape);
    renderWindow.draw(m_ClearButton.text);
}