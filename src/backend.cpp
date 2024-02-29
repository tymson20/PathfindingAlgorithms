#define SFML_STATIC

#include <iostream>
#include <SFML/Window/Mouse.hpp>
#include "backend.hpp"

// algorithms declarations
Solution dijkstra(Grid* const grid, Node* const startNode, Node* const destinationNode);

Backend::Backend(Grid* const grid, LegendBar* const legendBar, SettingsBar* const settingsBar, ButtonsBar* const buttonsBar)
    : m_LeftMouseButtonPressed(false), m_RightMouseButtonPressed(false), m_Grid(grid), m_LegendBar(legendBar), m_SettingsBar(settingsBar),
    m_ButtonsBar(buttonsBar), m_SelectedNodeType(Node::Type::Barrier), m_CurrentStartNode(nullptr), m_CurrentEndNode(nullptr),
    m_CurrentAlgorithm(Algorithm::Dijkstra) {}

void Backend::leftMouseButtonPressed(const sf::Vector2i& cursorPosition)
{   
    m_LeftMouseButtonPressed = true;
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
    if (m_LegendBar->getGlobalBounds().contains(cursorPositionFloat))
    {
        Node::Type selected = m_LegendBar->update(cursorPositionFloat);
        m_SelectedNodeType = selected != Node::Type::Empty ? selected : m_SelectedNodeType;
    }
    // Settings
    else if (m_SettingsBar->getGlobalBounds().contains(cursorPositionFloat))
    {
        std::cout << "Settings" << std::endl;
        auto result = m_SettingsBar->update(cursorPositionFloat);
        m_CurrentAlgorithm = result.first;
        m_Grid->setDiagonalMode(result.second);
    }
    // Buttons
    else if (m_ButtonsBar->getGlobalBounds().contains(cursorPositionFloat))
    {
        std::cout << "Buttons" << std::endl;
        ButtonsBar::ButtonType buttonType = m_ButtonsBar->update(cursorPositionFloat);
        if (buttonType == ButtonsBar::ButtonType::Start)
        {
            if (m_CurrentStartNode && m_CurrentEndNode && m_CurrentStartNode->getType() == Node::Type::Start && m_CurrentEndNode->getType() == Node::Type::End)
            {
                switch (m_CurrentAlgorithm)
                {
                    case Algorithm::Dijkstra:
                        std::cout << "Dijkstra" << std::endl;
                        m_Solution = dijkstra(m_Grid, m_CurrentStartNode, m_CurrentEndNode);
                        m_Solution.setSpeed(100.f);
                        m_Solution.start();
                        break;
                    case Algorithm::Astar:
                        std::cout << "A star" << std::endl;
                        break;
                    default:
                        break;
                }
            }
        }
        else if (buttonType == ButtonsBar::ButtonType::Clear)
        {
            m_Grid->clear();
        }

    }
}

void Backend::leftMouseButtonReleased()
{
    m_LeftMouseButtonPressed = false;
}

void Backend::rightMouseButtonPressed(const sf::Vector2i& cursorPosition)
{
    m_RightMouseButtonPressed = true;
}

void Backend::rightMouseButtonReleased()
{
    m_RightMouseButtonPressed = false;
}

void Backend::update(sf::RenderWindow& renderWindow)
{
    if (m_LeftMouseButtonPressed && m_SelectedNodeType == Node::Type::Barrier)
    {
        sf::Vector2f cursorPosition(sf::Mouse::getPosition(renderWindow));

        // Grid
        if (m_Grid->getGlobalBounds().contains(cursorPosition))
        {
            Node* node = m_Grid->setNodeType(cursorPosition, m_SelectedNodeType);
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
    }
    if (m_RightMouseButtonPressed)
    {
        sf::Vector2f cursorPosition(sf::Mouse::getPosition(renderWindow));

        // Grid
        if (m_Grid->getGlobalBounds().contains(cursorPosition))
        {
            m_Grid->setNodeType(cursorPosition, Node::Type::Empty);
        }
    }
    m_Solution.update();
}