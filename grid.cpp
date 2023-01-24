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

unsigned int Grid::lastMissingInRow(unsigned int y) const
{
    // create a vector with all the possible numbers
    std::vector<unsigned int> missingNumbers;
    for (unsigned int i = 1; i <= _size * _size; i++)
        missingNumbers.push_back(i);
    missingNumbers.push_back(_size * _size + 1);
    
    //sweep the Row and remove the already taken numbers
    for (unsigned int x = 0; x < _size * _size; x++)
    {
        if (find(missingNumbers.begin(), missingNumbers.end(), getCase(x, y)) != missingNumbers.end())
            missingNumbers.erase(find(missingNumbers.begin(), missingNumbers.end(), getCase(x, y)));
    }
    missingNumbers.pop_back();


    //if only one number is missing return it
    if(missingNumbers.size() == 1)
        return missingNumbers.back();

    //if not return 0
    return 0;
}

unsigned int Grid::lastMissingInColumn(unsigned int x) const
{
    // create a vector with all the possible numbers
    std::vector<unsigned int> missingNumbers;
    for (unsigned int i = 1; i <= _size * _size; i++)
        missingNumbers.push_back(i);
    missingNumbers.push_back(_size * _size + 1);

    //sweep the column and remove the already taken numbers
    for (unsigned int y = 0; y < _size * _size; y++)
    {
        if (find(missingNumbers.begin(), missingNumbers.end(), getCase(x, y)) != missingNumbers.end())
            missingNumbers.erase(find(missingNumbers.begin(), missingNumbers.end(), getCase(x, y)));
    }
    missingNumbers.pop_back();

    //if only one number is missing return it
    if(missingNumbers.size() == 1)
        return missingNumbers.back();

    //if not return 0
    return 0;
}

unsigned int Grid::lastMissingInSquare(unsigned int x, unsigned int y) const
{
    // create a vector with all the possible numbers
    std::vector<unsigned int> missingNumbers;
    for (unsigned int i = 1; i <= _size * _size; i++)
        missingNumbers.push_back(i);
    missingNumbers.push_back(_size * _size + 1);

    //sweep the square and remove the already taken numbers
    for (unsigned int i = 0; i < _size; i++)
    {
        for (unsigned int j = 0; j < _size; j++)
        {
            if (find(missingNumbers.begin(), missingNumbers.end(), getCase(x - x % _size + j, y - y % _size + i)) != missingNumbers.end())
                missingNumbers.erase(find(missingNumbers.begin(), missingNumbers.end(), getCase(x - x % _size + j, y - y % _size + i)));
        }
    }
    missingNumbers.pop_back();

    //if only one number is missing return it
    if(missingNumbers.size() == 1)
        return missingNumbers.back();

    //if not return 0
    return 0;
}

unsigned int Grid::getSize() const
{
    return _size;
}

unsigned int Grid::lastMissingNumber(unsigned int x, unsigned int y) const
{
    unsigned int lastMissingInRow = this->lastMissingInRow(y);
    unsigned int lastMissingInColumn = this->lastMissingInColumn(x);
    unsigned int lastMissingInSquare = this->lastMissingInSquare(x, y);

    if(lastMissingInRow != 0)
        return lastMissingInRow;
    else if(lastMissingInColumn != 0)
        return lastMissingInColumn;
    else if(lastMissingInSquare != 0)
        return lastMissingInSquare;
    else
        return 0;
}
