#define SFML_STATIC

#include <iostream>
#include "node.hpp"


const std::unordered_map<Node::Type, sf::Color> Node::s_MapColors = 
{
    {Node::Type::Empty, sf::Color::White},
    {Node::Type::Barrier, sf::Color(50, 50, 50)},
    {Node::Type::Start, sf::Color(0, 227, 13)},
    {Node::Type::End, sf::Color::Red},
    {Node::Type::Path, sf::Color(0, 40, 161)},
    {Node::Type::Visited, sf::Color(43, 96, 255)}
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