#ifndef SOLUTION_HPP
#define SOLUTION_HPP

#include <SFML/System/Clock.hpp>
#include <vector>
#include "node.hpp"

struct SolutionElement {
    Node* const node;
    const sf::Time time;
};

class Solution
{
public:
    Solution();

    void addElement(Node* const node, const sf::Time& time);

    void setSpeed(float speed) { m_Speed = speed; }

    void start();

    void stop() { m_ComputationsOngoing = false; }

    void update();

    void setPath(const std::vector<Node*>& path) { m_Path = path; }
    void drawPath();

private:
    std::size_t m_CurrentIdx;
    bool m_ComputationsOngoing;
    float m_Speed;
    sf::Clock m_Clock;
    std::vector<SolutionElement> m_ElementsVisited;
    std::vector<Node*> m_Path;
};

#endif // SOLUTION_HPP