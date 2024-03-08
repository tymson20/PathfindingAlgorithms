#define SFML_STATIC

#include <map>
#include <set>
#include <limits>
#include <algorithm>
#include <cmath>
#include <SFML/System/Clock.hpp>
#include "grid.hpp"
#include "solution.hpp"

std::size_t minDistanceIndex(const std::vector<bool>& visited, const std::vector<float>& distances)
{
    float minValue = std::numeric_limits<float>::max();
    std::size_t minIdx;
    for (std::size_t i = 0; i < visited.size(); i++)
    {
        if (!visited[i] && distances[i] < minValue)
        {
            minIdx = i;
            minValue = distances[i];
        }
    }
    return minIdx;
}

Solution dijkstra(Grid* const grid, Node* const startNode, Node* const destinationNode)
{
    Solution solution;
    sf::Clock clock;
    std::vector<Node*> nodes = grid->getNodes();
    std::vector<bool> visited(nodes.size(), false);
    std::vector<float> distances(nodes.size(), std::numeric_limits<float>::max());
    std::vector<Node*> previous(nodes.size(), NULL);
    std::map<Node*, std::size_t> mapIndex;
    for (std::size_t i = 0; i < nodes.size(); i++)
        mapIndex[nodes[i]] = i;
    
    distances[mapIndex[startNode]] = 0.f;
    Node* currentNode = startNode;

    while (true) {
        std::vector<std::pair<Node*, float>> neighbours = grid->getNeighbours(currentNode);
        for (auto neighbour : neighbours) {
            std::size_t neighbourIdx = mapIndex[neighbour.first];
            if (!visited[neighbourIdx]) {
                float distance = distances[mapIndex[currentNode]] + neighbour.second;
                if (distance < distances[neighbourIdx]) {
                    distances[neighbourIdx] = distance;
                    previous[neighbourIdx] = currentNode;
                }
            }
        }
        visited[mapIndex[currentNode]] = true;
        solution.addElement(currentNode, clock.getElapsedTime());

        Node* nearestNode = nullptr;
        if (currentNode == destinationNode) {
            // Algorithm reached destination node.
            std::vector<Node*> shortestPathReversed = {currentNode};
            while (currentNode != startNode) {
                Node* previousNode = previous[mapIndex[currentNode]];
                shortestPathReversed.push_back(previousNode);
                currentNode = previousNode;
            }
            solution.setPath({shortestPathReversed.crbegin(), shortestPathReversed.crend()});
            return solution;
        }
        else {
            nearestNode = nodes[minDistanceIndex(visited, distances)];
            if (distances[mapIndex[nearestNode]] == std::numeric_limits<int>::max()) {
                // There is no connection between nodes.
                return {};
            }
            else currentNode = nearestNode;
        }
    }
}

float manhattanHeuristic(Node* const node, Node* const destinationNode)
{
    return abs(destinationNode->m_IndexPosition.row - node->m_IndexPosition.row) + abs(destinationNode->m_IndexPosition.col - node->m_IndexPosition.col);
}

float diagonalHeuristic(Node* const node, Node* const destinationNode)
{
    float dx = abs(destinationNode->m_IndexPosition.col - node->m_IndexPosition.col);
    float dy = abs(destinationNode->m_IndexPosition.row - node->m_IndexPosition.row);
    return dx + dy + (sqrt(2) - 2) * std::min(dx, dy);
}

std::size_t minDistanceIndexAStar(const std::vector<bool>& visited, const std::vector<float>& distances, const std::vector<Node*>& nodes, Node* const destinationNode, bool diagonalMode)
{
    float minValue = std::numeric_limits<float>::max();
    std::size_t minIdx;
    for (std::size_t i = 0; i < visited.size(); i++)
    {
        float fullCost = distances[i] + (diagonalMode ? diagonalHeuristic(nodes[i], destinationNode) : manhattanHeuristic(nodes[i], destinationNode));
        if (!visited[i] && fullCost < minValue)
        {
            minIdx = i;
            minValue = fullCost;
        }
    }
    return minIdx;
}

Solution aStar(Grid* const grid, Node* const startNode, Node* const destinationNode)
{
    Solution solution;
    sf::Clock clock;
    std::vector<Node*> nodes = grid->getNodes();
    std::vector<bool> visited(nodes.size(), false);
    std::vector<float> costs(nodes.size(), std::numeric_limits<float>::max());
    std::vector<Node*> previous(nodes.size(), NULL);
    std::map<Node*, std::size_t> mapIndex;
    for (std::size_t i = 0; i < nodes.size(); i++)
        mapIndex[nodes[i]] = i;
    
    costs[mapIndex[startNode]] = 0.f;
    Node* currentNode = startNode;

    while (true) {
        std::vector<std::pair<Node*, float>> neighbours = grid->getNeighbours(currentNode);
        for (auto neighbour : neighbours) {
            std::size_t neighbourIdx = mapIndex[neighbour.first];
            if (!visited[neighbourIdx]) {
                float cost = costs[mapIndex[currentNode]] + neighbour.second;
                if (cost < costs[neighbourIdx]) {
                    costs[neighbourIdx] = cost;
                    previous[neighbourIdx] = currentNode;
                }
            }
        }
        visited[mapIndex[currentNode]] = true;
        solution.addElement(currentNode, clock.getElapsedTime());

        Node* nearestNode = nullptr;
        if (currentNode == destinationNode) {
            // Algorithm reached destination node.
            std::vector<Node*> shortestPathReversed = {currentNode};
            while (currentNode != startNode) {
                Node* previousNode = previous[mapIndex[currentNode]];
                shortestPathReversed.push_back(previousNode);
                currentNode = previousNode;
            }
            solution.setPath({shortestPathReversed.crbegin(), shortestPathReversed.crend()});
            return solution;
        }
        else {
            nearestNode = nodes[minDistanceIndexAStar(visited, costs, nodes, destinationNode, grid->getDiagonalMode())];
            if (costs[mapIndex[nearestNode]] == std::numeric_limits<int>::max()) {
                // There is no connection between nodes.
                return {};
            }
            else currentNode = nearestNode;
        }
    }
}