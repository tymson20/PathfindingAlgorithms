#ifndef BUTTONSBAR_HPP
#define BUTTONSBAR_HPP

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>

struct Button {
    sf::RectangleShape rectangleShape;
    sf::Text text;
};

class ButtonsBar
{
public:
    enum class ButtonType {None, Start, Clear};

public:
    ButtonsBar(const sf::Vector2f& position, const sf::Vector2f& size, const sf::Font& font);

    ButtonType update(const sf::Vector2f& cursorPosition);

    void draw(sf::RenderWindow& renderWindow) const;

    sf::FloatRect getGlobalBounds() const { return sf::FloatRect(m_Position, m_Size); }

private:
    const sf::Vector2f m_Position;
    const sf::Vector2f m_Size;
    Button m_StartButton;
    Button m_ClearButton;
};

#endif // BUTTONSBAR_HPP