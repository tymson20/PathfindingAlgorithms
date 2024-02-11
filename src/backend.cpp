#define SFML_STATIC

#include <iostream>
#include <stdexcept>
#include "backend.hpp"

Backend::Backend(Grid* const grid) : m_Grid(grid)
{

}

void Backend::leftMouseButtonCliked(const sf::Vector2i& cursorPosition)
{
    std::cout << cursorPosition.x << ", " << cursorPosition.y << std::endl;
    std::cout << (m_Grid->isPixelBelongs(cursorPosition) ? "Belongs" : "Doesn't belong") << std::endl;
    if (m_Grid->isPixelBelongs(cursorPosition))
        m_Grid->setNodeType(cursorPosition, Node::Type::Barrier);
}

void Backend::rightMouseButtonCliked(const sf::Vector2i& cursorPosition)
{
    if (m_Grid->isPixelBelongs(cursorPosition))
        m_Grid->setNodeType(cursorPosition, Node::Type::Empty);
}