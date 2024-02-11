#ifndef BACKEND_HPP
#define BACKEND_HPP

#include "grid.hpp"

class Backend
{
public:
    Backend(Grid* const grid);

    void leftMouseButtonCliked(const sf::Vector2i& cursorPosition);

    void rightMouseButtonCliked(const sf::Vector2i& cursorPosition);

private:
    Grid* const m_Grid;
};

#endif // BACKEND_HPP