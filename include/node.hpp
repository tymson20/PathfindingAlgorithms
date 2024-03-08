#ifndef NODE_HPP
#define NODE_HPP

#include <SFML/Graphics/RectangleShape.hpp>
#include <unordered_map>

class Node : public sf::RectangleShape
{
public:
    enum class Type {Empty, Barrier, Start, End, Path, Visited};

    struct IndexPosition
    {
        unsigned int row;
        unsigned int col;
    };

private:
    static const std::unordered_map<Type, sf::Color> s_MapColors;

public:
    Node(unsigned int row, unsigned int col, const sf::Vector2f& position, const sf::Vector2f& size, Type type = Type::Empty);

    void setType(Type type);

    Type getType() const { return m_Type; }

public:
    const IndexPosition m_IndexPosition;

private:
    Type m_Type;
};



#endif // NODE_HPP