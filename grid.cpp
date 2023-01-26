#include "grid.h"

Grid::Grid(unsigned int size, unsigned int difficulty)
        : _size(size)
{
    if (difficulty > 7)
        _difficulty = 7;
    if (difficulty < 1)
        _difficulty = 1;
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

    //sweep throught the column and remove the already taken numbers
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

unsigned int Grid::getDifficulty() const
{
    return _difficulty;
}

void Grid::generateStartingGrid(bool removeValue)
{
    srand(time(NULL)); // initialisation of the randomizer

    // fill the grid
    int i = 0;
    for (int n = 0; n < pow(_size, 4); n++)
    {
        if (n % (_size * _size) == 0 && n != 0)
            i += _size;
        if (n % (_size * _size * _size) == 0 && n != 0)
            i++;
        _grid.at(n) = n + i;
    }

    for (int n = 0; n < pow(_size, 4); n++)
    {
        // set the range of value between 1 and _size * _size to set the value in the good range
        _grid.at(n) = _grid.at(n) % (_size * _size) + 1;
    }
    shuffleGrid();

    // remove random numbers to match the difficulty
    if (removeValue)
    {
        std::array<float, 7> possibleValue = {0.8, 0.7, 0.6, 0.5, 0.4, 0.3, 0.2};
        unsigned int amountToGenerate = int(possibleValue.at(_difficulty - 1) * pow(_size, 4));
        for (unsigned int i = 0; i < pow(_size, 4) - amountToGenerate; i++)
        {
            unsigned int x = 0, y = 0;
            do
            {
                x = rand() % (_size * _size);
                y = rand() % (_size * _size);
            } while (getCase(x, y) == 0);
            setCase(x, y, 0);
        }
    }
}

void Grid::shuffleGrid()
{
    for (int i = 0; i < pow(_size, 5); i++)
    {
        int x1 = rand() % (_size * _size);
        int x2 = rand() % (_size * _size);

        if ((abs(x1 - x2) < _size) && (x1 != x2) && (x1 / _size == x2 / _size))
        {
            swapRows(x1, x2);
        }
        else if (x1 % _size == x2 % _size && x1 != x2)
        {
            for (unsigned int i = 0; i < _size; ++i)
                swapRows(x1 - x1 % _size + i, x2 - x2 % _size + i);
        }

        x1 = rand() % (_size * _size);
        x2 = rand() % (_size * _size);

        if ((abs(x1 - x2) < _size) && (x1 != x2) && (x1 / _size == x2 / _size))
        {
            swapColumns(x1, x2);
        }
        else if (x1 % _size == x2 % _size && x1 != x2)
        {
            for (unsigned int i = 0; i < _size; ++i)
                swapColumns(x1 - x1 % _size + i, x2 - x2 % _size + i);
        }

        x1 = rand() % (_size * _size) + 1;
        x2 = rand() % (_size * _size) + 1;

        if (x1 != x2)
        {
            swapValue(x1, x2);
        }
    }
}

void Grid::swapRows(unsigned int row1, unsigned int row2)
{
    for (unsigned int i = 0; i < _size * _size; ++i)
    {
        unsigned int tmp = getCase(i, row1);
        setCase(i, row1, getCase(i, row2));
        setCase(i, row2, tmp);
    }
}

void Grid::swapColumns(unsigned int column1, unsigned int column2)
{
    for (unsigned int i = 0; i < _size * _size; ++i)
    {
        unsigned int tmp = getCase(column1, i);
        setCase(column1, i, getCase(column2, i));
        setCase(column2, i, tmp);
    }
}

void Grid::swapValue(unsigned int value1, unsigned int value2)
{
    for (unsigned int i = 0; i < _size * _size; ++i)
    {
        for (unsigned int j = 0; j < _size * _size; ++j)
        {
            if (getCase(i, j) == value1)
                setCase(i, j, value2);
            else if (getCase(i, j) == value2)
                setCase(i, j, value1);
        }
    }
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
