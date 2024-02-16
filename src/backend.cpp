#define SFML_STATIC

#include <iostream>
#include "backend.hpp"

Backend::Backend(Grid* const grid, LegendBar* const legendBar, SettingsBar* const settingsBar, ButtonsBar* const buttonsBar)
    : m_Grid(grid), m_LegendBar(legendBar), m_SettingsBar(settingsBar), m_ButtonsBar(buttonsBar), m_SelectedNodeType(Node::Type::Barrier),
    m_CurrentStartNode(nullptr), m_CurrentEndNode(nullptr), m_CurrentAlgorithm(Algorithm::Dijkstra) {}

void Backend::leftMouseButtonCliked(const sf::Vector2i& cursorPosition)
{
    //std::cout << cursorPosition.x << ", " << cursorPosition.y << std::endl;
    //std::cout << (m_Grid->getGlobalBounds().contains(sf::Vector2f(cursorPosition)) ? "Belongs" : "Doesn't belong") << std::endl;

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
    // Settings
    else if (m_SettingsBar->getGlobalBounds().contains(cursorPositionFloat))
    {
        std::cout << "Settings" << std::endl;
        m_CurrentAlgorithm = m_SettingsBar->update(cursorPositionFloat);
    }
    // Buttons
    else if (m_ButtonsBar->getGlobalBounds().contains(cursorPositionFloat))
    {
        std::cout << "Buttons" << std::endl;
        ButtonsBar::ButtonType buttonType = m_ButtonsBar->update(cursorPositionFloat);
        if (buttonType == ButtonsBar::ButtonType::Start)
        {
            switch (m_CurrentAlgorithm)
            {
                case Algorithm::Dijkstra:
                    std::cout << "Dijkstra" << std::endl;
                    break;
                case Algorithm::Astar:
                    std::cout << "A star" << std::endl;
                    break;
                default:
                    break;
            }
        }
        else if (buttonType == ButtonsBar::ButtonType::Clear)
        {
            m_Grid->clear();
        }

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