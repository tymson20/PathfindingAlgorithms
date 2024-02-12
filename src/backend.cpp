#define SFML_STATIC

#include <iostream>
#include "backend.hpp"

Backend::Backend(Grid* const grid, LegendBar* const legendBar)
: m_Grid(grid), m_LegendBar(legendBar), m_SelectedNodeType(Node::Type::Barrier), m_CurrentStartNode(nullptr), m_CurrentEndNode(nullptr) {}

void Backend::leftMouseButtonCliked(const sf::Vector2i& cursorPosition)
{
    std::cout << cursorPosition.x << ", " << cursorPosition.y << std::endl;
    std::cout << (m_Grid->getGlobalBounds().contains(sf::Vector2f(cursorPosition)) ? "Belongs" : "Doesn't belong") << std::endl;

    sf::Vector2f cursorPositionFloat(cursorPosition);
    
    // Grid
    if (m_Grid->getGlobalBounds().contains(cursorPositionFloat))
    {
        Node* node = m_Grid->setNodeType(cursorPositionFloat, m_SelectedNodeType);
        if (node)
        {
            if (m_SelectedNodeType == Node::Type::Start)
            {
                if (m_CurrentStartNode)
                    m_CurrentStartNode->setType(Node::Type::Empty);
                m_CurrentStartNode = node;
            }
            else if (m_SelectedNodeType == Node::Type::End)
            {
                if (m_CurrentEndNode)
                    m_CurrentEndNode->setType(Node::Type::Empty);
                m_CurrentEndNode = node;
            }
        }
    }
    // Legend
    else if (m_LegendBar->getGlobalBounds().contains(cursorPositionFloat))
    {
        Node::Type selected = m_LegendBar->update(cursorPositionFloat);
        m_SelectedNodeType = selected != Node::Type::Empty ? selected : m_SelectedNodeType;
    }
}

void Backend::rightMouseButtonCliked(const sf::Vector2i& cursorPosition)
{
    sf::Vector2f cursorPositionFloat(cursorPosition);
    // Grid
    if (m_Grid->getGlobalBounds().contains(cursorPositionFloat))
    {
        m_Grid->setNodeType(cursorPositionFloat, Node::Type::Empty);
    }
}