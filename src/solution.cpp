#define SFML_STATIC

#include "solution.hpp"

Solution::Solution() : m_CurrentIdx(1), m_ComputationsOngoing(false), m_Speed(1.f) {}

void Solution::addElement(Node* const node, const sf::Time& time)
{
    m_ElementsVisited.push_back({node, time});
}

void Solution::start()
{
    m_CurrentIdx = 1;
    m_ComputationsOngoing = true;
    m_Clock.restart();
}

void Solution::update()
{
    if (m_ComputationsOngoing)
    {
        if (m_CurrentIdx >= m_ElementsVisited.size())
        {
            drawPath();
            stop();
        }
        else if (m_Clock.getElapsedTime() >= m_ElementsVisited[m_CurrentIdx].time * m_Speed)
        {
            m_ElementsVisited[m_CurrentIdx].node->setType(Node::Type::Visited);
            m_CurrentIdx++;
        }
    }
}

void Solution::drawPath()
{
    for (auto it = m_Path.cbegin() + 1; it < m_Path.cend() - 1; it++)
    {
        (*it)->setType(Node::Type::Path);
    }
    m_Path[0]->setType(Node::Type::Start);
    m_Path[m_Path.size() - 1]->setType(Node::Type::End);
}