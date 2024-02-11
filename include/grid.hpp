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
// rows - number of nodes in height (number of rows)
// columns - number of nodes in width (number of columns)
    Grid(const sf::Vector2f& position, const sf::Vector2f& nodeSize, float gapWidth, unsigned int rows, unsigned int columns);

    void draw(sf::RenderWindow& renderWindow) const;

    bool isPixelBelongs(const sf::Vector2i cursorPosition) const;

    void setNodeType(const sf::Vector2i& cursorPosition, Node::Type type);

private:
    const sf::Vector2f m_Position;
    const sf::Vector2f m_NodeSize;
    const float m_GapWidth;
    const unsigned int m_Rows, m_Columns;
    const sf::Vector2f m_Size;
    std::vector<std::vector<Node>> m_Matrix;
};

#endif // GRID_HPP