#ifndef GRID_HPP
#define GRID_HPP

#include <vector>
#include <SFML/Graphics/RenderWindow.hpp>
#include "node.hpp"

class Grid
{
public:
// postion - position of the top left corner
// nodeSize - size of nodes
// gapWidth - gap width beetwen nodes
// width - number of nodes in width
// height - number of nodes in height
    Grid(const sf::Vector2f& position, const sf::Vector2f& nodeSize, float gapWidth, unsigned int width, unsigned int height);

    void draw(sf::RenderWindow& renderWindow) const;

    void setNodeType(const sf::Vector2u& nodePosition, Node::Type type);

private:
    std::vector<std::vector<Node>> m_Matrix;
};

#endif // GRID_HPP