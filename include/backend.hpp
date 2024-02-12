#ifndef BACKEND_HPP
#define BACKEND_HPP

#include "grid.hpp"
#include "legendBar.hpp"

class Backend
{
public:
    Backend(Grid* const grid, LegendBar* const legendBar);

    void leftMouseButtonCliked(const sf::Vector2i& cursorPosition);

    void rightMouseButtonCliked(const sf::Vector2i& cursorPosition);

private:
    Grid* const m_Grid;
    LegendBar* const m_LegendBar;
    Node::Type m_SelectedNodeType;
    Node* m_CurrentStartNode;
    Node* m_CurrentEndNode;
};

#endif // BACKEND_HPP