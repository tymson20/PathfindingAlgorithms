#define SFML_STATIC

#include <iostream>
#include <stdexcept>
#include <cmath>
#include "grid.hpp"

Grid::Grid(const sf::Vector2f& position, const sf::Vector2f& nodeSize, float gapWidth, unsigned int rows, unsigned int columns, sf::Color fillColor, sf::Color outlineColor)
    : RectangleShape(sf::Vector2f((float)columns * nodeSize.x + (float)(columns - 1) * gapWidth, (float)rows * nodeSize.y + (float)(rows - 1) * gapWidth)),
    m_NodeSize(nodeSize), m_GapWidth(gapWidth), m_Rows(rows), m_Columns(columns), m_DiagonalMode(false)
{
    if (nodeSize.x < 0.f || nodeSize.y < 0.f)
        throw std::invalid_argument("The nodeSize argument should has positive values!");
    if (gapWidth < 0.f)
        throw std::invalid_argument("The gapWidth argument should be positive!");
    setPosition(position);
    setFillColor(fillColor);
    setOutlineColor(outlineColor);
    setOutlineThickness(5.f);
    float pos_X = getPosition().x, pos_Y = getPosition().y;
    m_Matrix = std::vector<std::vector<Node>>();
    m_Matrix.reserve(rows);

    for (std::size_t row = 0; row < rows; row++)
    {
        std::vector<Node> rowVector;
        rowVector.reserve(columns);
        for (std::size_t col = 0; col < columns; col++)
        {
            rowVector.emplace_back(std::move(Node(row, col, {pos_X, pos_Y}, nodeSize)));
            pos_X += (gapWidth + nodeSize.x);
        }
        pos_Y += (gapWidth + nodeSize.y);
        pos_X = position.x;
        m_Matrix.push_back(rowVector);
    }
}

void Grid::draw(sf::RenderWindow& renderWindow) const
{
    renderWindow.draw(*this);
    for (const auto& row : m_Matrix)
    {
        for (const Node& node : row)
        {
            renderWindow.draw(node);
        }
    }
}

Node* Grid::setNodeType(const sf::Vector2f& cursorPosition, Node::Type type)
{
    if (cursorPosition.x < getPosition().x || cursorPosition.x > getPosition().x + getSize().x ||
        cursorPosition.y < getPosition().y || cursorPosition.y > getPosition().y + getSize().y)
    {
        //std::cout << "You clicked on the outline" << std::endl;
        return nullptr;
    }
    static const float gapDetectRowValue = m_NodeSize.y/(m_NodeSize.y + m_GapWidth);
    static const float gapDetectColValue = m_NodeSize.x/(m_NodeSize.x + m_GapWidth);
    float rowFloat, colFloat;
    rowFloat = (cursorPosition.y - getPosition().y)/(m_NodeSize.y + m_GapWidth);
    colFloat = (cursorPosition.x - getPosition().x)/(m_NodeSize.x + m_GapWidth);
    if ((rowFloat - (int)rowFloat) <= gapDetectRowValue && (colFloat - (int)colFloat) <= gapDetectColValue)
    {
        Node* node = &m_Matrix[(unsigned int)rowFloat][(unsigned int)colFloat];
        node->setType(type);
        return node;
    }
    else
    {
        //std::cout << "You clicked on the gap." << std::endl;
        return nullptr;
    }
}

std::vector<Node*> Grid::getNodes()
{
    std::vector<Node*> nodes;
    nodes.reserve(m_Rows * m_Columns);
    for (auto& row : m_Matrix)
        for (std::size_t i = 0; i < m_Columns; i++)
            nodes.push_back(&(row[i]));
    return nodes;
}

std::vector<std::pair<Node*, float>> Grid::getNeighbours(Node* node)
{
    bool up = false, down = false, left = false, right = false;
    bool upEmpty = false, downEmpty = false, leftEmpty = false, rightEmpty = false;
    std::vector<std::pair<Node*, float>> neighbours;
    neighbours.reserve(8);

    if (node->m_IndexPosition.row != 0)
        up = true;
    if (node->m_IndexPosition.row != m_Rows-1)
        down = true;
    if (node->m_IndexPosition.col != 0)
        left = true;
    if (node->m_IndexPosition.col != m_Columns-1)
        right = true;
    if (up && m_Matrix[node->m_IndexPosition.row-1][node->m_IndexPosition.col].getType() != Node::Type::Barrier)
    {
        upEmpty = true;
        neighbours.emplace_back(&(m_Matrix[node->m_IndexPosition.row-1][node->m_IndexPosition.col]), 1.f);
    }
    if (down && m_Matrix[node->m_IndexPosition.row+1][node->m_IndexPosition.col].getType() != Node::Type::Barrier)
    {
        downEmpty = true;
        neighbours.emplace_back(&(m_Matrix[node->m_IndexPosition.row+1][node->m_IndexPosition.col]), 1.f);
    }
    if (left && m_Matrix[node->m_IndexPosition.row][node->m_IndexPosition.col-1].getType() != Node::Type::Barrier)
    {
        leftEmpty = true;
        neighbours.emplace_back(&(m_Matrix[node->m_IndexPosition.row][node->m_IndexPosition.col-1]), 1.f);
    }
    if (right && m_Matrix[node->m_IndexPosition.row][node->m_IndexPosition.col+1].getType() != Node::Type::Barrier)
    {
        rightEmpty = true;
        neighbours.emplace_back(&(m_Matrix[node->m_IndexPosition.row][node->m_IndexPosition.col+1]), 1.f);
    }
    if (m_DiagonalMode)
    {
        const float value = sqrt(2);
        if (up && left && m_Matrix[node->m_IndexPosition.row-1][node->m_IndexPosition.col-1].getType() != Node::Type::Barrier && (upEmpty || leftEmpty))
            neighbours.emplace_back(&(m_Matrix[node->m_IndexPosition.row-1][node->m_IndexPosition.col-1]), value);
        if (up && right && m_Matrix[node->m_IndexPosition.row-1][node->m_IndexPosition.col+1].getType() != Node::Type::Barrier && (upEmpty || rightEmpty))
            neighbours.emplace_back(&(m_Matrix[node->m_IndexPosition.row-1][node->m_IndexPosition.col+1]), value);
        if (down && left && m_Matrix[node->m_IndexPosition.row+1][node->m_IndexPosition.col-1].getType() != Node::Type::Barrier && (downEmpty || leftEmpty))
            neighbours.emplace_back(&(m_Matrix[node->m_IndexPosition.row+1][node->m_IndexPosition.col-1]), value);
        if (down && right && m_Matrix[node->m_IndexPosition.row+1][node->m_IndexPosition.col+1].getType() != Node::Type::Barrier && (downEmpty || rightEmpty))
            neighbours.emplace_back(&(m_Matrix[node->m_IndexPosition.row+1][node->m_IndexPosition.col+1]), value);
    }
    
    neighbours.shrink_to_fit();
    return neighbours;
}

void Grid::clear()
{
    for (auto& row : m_Matrix)
    {
        for (Node& node : row)
            if (node.getType() != Node::Type::Barrier)
                node.setType(Node::Type::Empty);
    }
}

void Grid::clearAll()
{
    for (auto& row : m_Matrix)
    {
        for (Node& node : row)
            node.setType(Node::Type::Empty);
    }
}