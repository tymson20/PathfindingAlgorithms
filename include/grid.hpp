#ifndef GRID_HPP
#define GRID_HPP

#include <vector>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include "node.hpp"

class Grid : public sf::RectangleShape
{
public:
// postion - position of the top left corner
// nodeSize - size of nodes
// gapWidth - gap width beetwen nodes
// rows - number of nodes in height (number of rows)
// columns - number of nodes in width (number of columns)
    Grid(const sf::Vector2f& position, const sf::Vector2f& nodeSize, float gapWidth, unsigned int rows, unsigned int columns, sf::Color fillColor, sf::Color outlineColor);

    void draw(sf::RenderWindow& renderWindow) const;

    Node* setNodeType(const sf::Vector2f& cursorPosition, Node::Type type);

    std::vector<Node*> getNodes();

    std::vector<std::pair<Node*, float>> getNeighbours(Node* node);

    void clear();
    void clearAll();

    bool getDiagonalMode() const { return m_DiagonalMode; }
    void setDiagonalMode(bool diagonal) { m_DiagonalMode = diagonal; }

private:
    const sf::Vector2f m_NodeSize;
    const float m_GapWidth;
    const unsigned int m_Rows, m_Columns;
    bool m_DiagonalMode;
    std::vector<std::vector<Node>> m_Matrix;
};

#endif // GRID_HPP