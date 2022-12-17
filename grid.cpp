#include "grid.h"

Grid::Grid(unsigned int size)
    : _size(size)
{
    _grid.resize(pow(_size, 4), 0);
}

unsigned int Grid::getCase(unsigned int x, unsigned int y) const
{
    return _grid.at(y * _size * _size + x);
}

void Grid::setCase(unsigned int x, unsigned int y, unsigned int value)
{
    _grid.at(y * _size * _size + x) = value;
}

void Grid::at(unsigned int n)
{
    _grid.at(n);
}

std::ostream &operator<<(std::ostream &os, const Grid &grid) // << overload to print the grid
{
    for (unsigned int i = 0; i < 2 * (grid._size * grid._size + grid._size) + 1; i++)
        os << "-";
    os << std::endl;
    for (unsigned int y = 0; y < grid._size * grid._size; y++)
    {
        os << "| ";
        for (unsigned int x = 0; x < grid._size * grid._size; x++)
        {
            if (x % grid._size == 0 && x != 0)
                os << "| ";

            int caseValue = grid.getCase(x, y);
            caseValue == 0 ? os << "·" : os << caseValue;
            caseValue >= 10 ? os << "" : os << " ";
        }
        os << "|";
        os << std::endl;
        if ((y + 1) % grid._size == 0 && y != 0 && y != grid._size * grid._size - 1)
        {
            for (unsigned int i = 0; i < 2 * (grid._size * grid._size + grid._size) + 1; i++)
                os << "-";
            os << std::endl;
        }
    }
    for (unsigned int i = 0; i < 2 * (grid._size * grid._size + grid._size) + 1; i++)
        os << "-";
    os << std::endl;
    return os;
}

std::vector<unsigned int>& Grid::getGrid()
{
    return _grid;
}