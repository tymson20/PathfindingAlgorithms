#define SFML_STATIC

#include <map>
#include <set>
#include <limits>
#include <algorithm>
#include <SFML/System/Clock.hpp>
#include "grid.hpp"
#include "solution.hpp"

Solution dijkstra(Grid* const grid, Node* const startNode, Node* const destinationNode)
{
    Solution solution;
    sf::Clock clock;
    std::vector<Node*> nodes = grid->getNodes();
    std::map<Node*, float> distances;
    std::map<Node*, Node*> previous;
    for (Node* node : nodes) {
        distances[node] = std::numeric_limits<float>::max();
        previous[node] = NULL;
    }
    distances[startNode] = 0.f;
    std::set<Node*> unvisitedSet(nodes.cbegin(), nodes.cend());
    Node* currentNode = startNode;

    auto compareDistance = [&distances](Node* const node1, Node* const node2) {
        return distances[node1] < distances[node2];
    };

    while (true) {
        std::vector<std::pair<Node*, float>> neighbours = grid->getNeighbours(currentNode);
        for (auto neighbour : neighbours) {
            if (unvisitedSet.find(neighbour.first) != unvisitedSet.cend()) {
                float distance = distances[currentNode] + neighbour.second;
                if (distance < distances[neighbour.first]) {
                    distances[neighbour.first] = distance;
                    previous[neighbour.first] = currentNode;
                }
            }
        }
        unvisitedSet.erase(currentNode);
        solution.addElement(currentNode, clock.getElapsedTime());

        Node* nearestNode = nullptr;
        if (currentNode == destinationNode) {
            // Algorithm reached destination node.
            std::vector<Node*> shortestPathReversed = {currentNode};
            while (currentNode != startNode) {
                Node* previousNode = previous[currentNode];
                shortestPathReversed.push_back(previousNode);
                currentNode = previousNode;
            }
            solution.setPath({shortestPathReversed.crbegin(), shortestPathReversed.crend()});
            return solution;
        }
        else {
            nearestNode = *std::min_element(unvisitedSet.cbegin(), unvisitedSet.cend(), compareDistance);
            if (distances[nearestNode] == std::numeric_limits<int>::max()) {
                // There is no connection between nodes.
                return solution;
            }
            else currentNode = nearestNode;
        }
    }
}