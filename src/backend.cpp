#define SFML_STATIC

#include <iostream>
#include "backend.hpp"

Backend::Backend(Grid* const grid) : m_Grid(grid) {}

void Backend::leftMouseButtonCliked(const sf::Vector2i& cursorPosition)
{
    std::cout << cursorPosition.x << ", " << cursorPosition.y << std::endl;
    std::cout << (m_Grid->getGlobalBounds().contains(sf::Vector2f(cursorPosition)) ? "Belongs" : "Doesn't belong") << std::endl;
    if (m_Grid->getGlobalBounds().contains(sf::Vector2f(cursorPosition)))
        m_Grid->setNodeType(cursorPosition, Node::Type::Barrier);
}

void Backend::rightMouseButtonCliked(const sf::Vector2i& cursorPosition)
{
    if (m_Grid->getGlobalBounds().contains(sf::Vector2f(cursorPosition)))
        m_Grid->setNodeType(cursorPosition, Node::Type::Empty);
}