#define SFML_STATIC

#include "grid.hpp"


Grid::Grid(const sf::Vector2f& position, const sf::Vector2f& nodeSize, float gapWidth, unsigned int width, unsigned int height)
{
    float pos_X = position.x, pos_Y = position.y;
    m_Matrix = std::vector<std::vector<Node>>();
    m_Matrix.reserve(height);

    for (std::size_t row = 0; row < height; row++)
    {
        std::vector<Node> rowVector;
        rowVector.reserve(width);
        for (std::size_t col = 0; col < width; col++)
        {
            rowVector.emplace_back(std::move(Node({pos_X, pos_Y}, nodeSize)));
            pos_X += (gapWidth + nodeSize.x);
        }
        pos_Y += (gapWidth + nodeSize.y);
        pos_X = position.x;
        m_Matrix.push_back(rowVector);
    }
}

void Grid::draw(sf::RenderWindow& renderWindow) const
{
    for (const auto& row : m_Matrix)
    {
        for (const Node& node : row)
        {
            renderWindow.draw(node);
        }
    }
}

void Grid::setNodeType(const sf::Vector2u& nodePosition, Node::Type type)
{
    m_Matrix[nodePosition.y][nodePosition.x].setType(type);
}