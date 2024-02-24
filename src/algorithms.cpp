#include <map>
#include <set>
#include <limits>
#include <algorithm>
#include "grid.hpp"

void dijkstra(Grid* const grid, Node* const startNode, Node* const destinationNode)
{
    std::vector<Node*> nodes = grid->getNodes();
    std::map<Node*, int> distances;
    std::map<Node*, Node*> previous;
    for (Node* node : nodes) {
        distances[node] = std::numeric_limits<int>::max();
        previous[node] = NULL;
    }
    distances[startNode] = 0;
    std::set<Node*> unvisitedSet(nodes.cbegin(), nodes.cend());
    Node* currentNode = startNode;

    auto compareDistance = [&distances](Node* const node1, Node* const node2) {
        return distances[node1] < distances[node2];
    };

    while (true) {
        std::vector<Node*> neighbours = grid->getNeighbours(currentNode);
        for (auto neighbour : neighbours) {
            if (unvisitedSet.find(neighbour) != unvisitedSet.cend()) {
                int distance = distances[currentNode] + 1;
                if (distance < distances[neighbour]) {
                    distances[neighbour] = distance;
                    previous[neighbour] = currentNode;
                }
            }
        }
        unvisitedSet.erase(currentNode);
        currentNode->setType(Node::Type::Visited);

        Node* nearestNode = nullptr;
        if (currentNode == destinationNode) {
            // Algorithm reached destination node.
            std::vector<Node*> shortestPathReversed = {currentNode};
            while (currentNode != startNode) {
                Node* previousNode = previous[currentNode];
                shortestPathReversed.push_back(previousNode);
                currentNode = previousNode;
            }
            //*cost = distances[destinationNode];
            //std::vector<Node*> shortestPath(shortestPathReversed.rbegin(), shortestPathReversed.rend());
            //return shortestPath;
            for (auto it = shortestPathReversed.rbegin(); it < shortestPathReversed.rend(); it++)
                (*it)->setType(Node::Type::Path);
            startNode->setType(Node::Type::Start);
            destinationNode->setType(Node::Type::End);
            return;
        }
        else {
            nearestNode = *std::min_element(unvisitedSet.cbegin(), unvisitedSet.cend(), compareDistance);
            if (distances[nearestNode] == std::numeric_limits<int>::max()) {
                // There is no connection between nodes.
                //*cost = -1;
                //return {};
                return;
            }
            else currentNode = nearestNode;
        }
    }
}