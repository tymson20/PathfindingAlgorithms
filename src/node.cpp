#define SFML_STATIC

#include <iostream>
#include "node.hpp"


const std::unordered_map<Node::Type, sf::Color> Node::s_MapColors = 
{
    {Node::Type::Empty, sf::Color::White},
    {Node::Type::Barrier, sf::Color(50, 50, 50)},
    {Node::Type::Start, sf::Color::Red},
    {Node::Type::End, sf::Color(0, 227, 13)},
    {Node::Type::Path, sf::Color(0, 93, 199)},
    {Node::Type::Visited, sf::Color(110, 175, 250)}
};

Node::Node(unsigned int row, unsigned int column, const sf::Vector2f& position, const sf::Vector2f& size, Type type)
    : RectangleShape(size), m_IndexPosition({row, column})
{
    setPosition(position);
    setType(type);
}

void Node::setType(Type type)
{
    m_Type = type;
    setFillColor(s_MapColors.at(type));
}