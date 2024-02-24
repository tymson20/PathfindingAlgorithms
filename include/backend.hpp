#ifndef BACKEND_HPP
#define BACKEND_HPP

#include "SFML/Graphics/RenderWindow.hpp"
#include "grid.hpp"
#include "legendBar.hpp"
#include "settingsBar.hpp"
#include "buttonsBar.hpp"

class Backend
{
public:
    Backend(Grid* const grid, LegendBar* const legendBar, SettingsBar* const settingsBar, ButtonsBar* const buttonsBar);

    void leftMouseButtonPressed(const sf::Vector2i& cursorPosition);
    void leftMouseButtonReleased();

    void rightMouseButtonPressed(const sf::Vector2i& cursorPosition);
    void rightMouseButtonReleased();

    void update(sf::RenderWindow& renderWindow);

private:
    bool m_LeftMouseButtonPressed;
    bool m_RightMouseButtonPressed;
    Grid* const m_Grid;
    LegendBar* const m_LegendBar;
    SettingsBar* const m_SettingsBar;
    ButtonsBar* const m_ButtonsBar;
    Node::Type m_SelectedNodeType;
    Node* m_CurrentStartNode;
    Node* m_CurrentEndNode;
    Algorithm m_CurrentAlgorithm;
};

#endif // BACKEND_HPP