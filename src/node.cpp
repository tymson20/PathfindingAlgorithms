#define SFML_STATIC

#include <iostream>
#include "node.hpp"


const std::unordered_map<Node::Type, sf::Color> Node::s_MapColors = 
{
    {Node::Type::Empty, sf::Color::White},
    {Node::Type::Barrier, sf::Color()},
    {Node::Type::Start, sf::Color::Green},
    {Node::Type::End, sf::Color::Red},
    {Node::Type::Path, sf::Color()},
    {Node::Type::Visited, sf::Color()}
};

Node::Node(const sf::Vector2f& position, const sf::Vector2f& size, Type type) : RectangleShape(size)
{
    setPosition(position);
    setType(type);
}

void Node::setType(Type type)
{
    m_Type = type;
    setFillColor(s_MapColors.at(type));
}