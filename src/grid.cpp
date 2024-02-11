#define SFML_STATIC

#include <iostream>
#include <stdexcept>
#include "grid.hpp"

Grid::Grid(const sf::Vector2f& position, const sf::Vector2f& nodeSize, float gapWidth, unsigned int rows, unsigned int columns)
    : m_Position(position), m_NodeSize(nodeSize), m_GapWidth(gapWidth), m_Rows(rows), m_Columns(columns),
    m_Size(sf::Vector2f((float)columns * nodeSize.x + (float)(columns - 1) * gapWidth, (float)rows * nodeSize.y + (float)(rows - 1) * gapWidth))
{
    if (nodeSize.x < 0.f || nodeSize.y < 0.f)
        throw std::invalid_argument("The nodeSize argument should has positive values!");
    if (gapWidth < 0.f)
        throw std::invalid_argument("The gapWidth argument should be positive!");
    float pos_X = position.x, pos_Y = position.y;
    m_Matrix = std::vector<std::vector<Node>>();
    m_Matrix.reserve(rows);

    for (std::size_t row = 0; row < rows; row++)
    {
        std::vector<Node> rowVector;
        rowVector.reserve(columns);
        for (std::size_t col = 0; col < columns; col++)
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

bool Grid::isPixelBelongs(const sf::Vector2i cursorPosition) const
{
    if (cursorPosition.x >= m_Position.x && cursorPosition.x <= m_Position.x + m_Size.x &&
        cursorPosition.y >= m_Position.y && cursorPosition.y <= m_Position.y + m_Size.y)
        return true;
    else
        return false;
}

void Grid::setNodeType(const sf::Vector2i& cursorPosition, Node::Type type)
{
    static const float gapDetectRowValue = m_NodeSize.y/(m_NodeSize.y + m_GapWidth);
    static const float gapDetectColValue = m_NodeSize.x/(m_NodeSize.x + m_GapWidth);
    float rowFloat, colFloat;
    rowFloat = ((float)cursorPosition.y - m_Position.y)/(m_NodeSize.y + m_GapWidth);
    colFloat = ((float)cursorPosition.x - m_Position.x)/(m_NodeSize.x + m_GapWidth);
    if ((rowFloat - (int)rowFloat) <= gapDetectRowValue && (colFloat - (int)colFloat) <= gapDetectColValue)
        m_Matrix[(unsigned int)rowFloat][(unsigned int)colFloat].setType(type);
    else
        std::cout << "You clicked on the gap." << std::endl;
}