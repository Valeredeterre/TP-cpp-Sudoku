#include "sudoku.h"

Sudoku::Sudoku()
: _dificulty(1), _size(3)
{
    srand(time(NULL));
    _grid.resize(pow(_size, 4));
}

Sudoku::Sudoku(unsigned int dificulty)
: _dificulty(dificulty), _size(3)
{
    srand(time(NULL));
    _grid.resize(pow(_size, 4));
}

Sudoku::Sudoku(unsigned int dificulty, unsigned int size)
: _dificulty(dificulty), _size(size)
{
    srand(time(NULL));
    _grid.resize(pow(_size, 4));
}

unsigned int Sudoku::getCase(unsigned int x, unsigned int y) const
{
    return _grid.at(y * _size + x);
}

void Sudoku::setCase(unsigned int x, unsigned int y, unsigned int value)
{
    _grid.at(y * _size + x) = value;
}

std::ostream& operator<<(std::ostream& os, const Sudoku& sudoku)
{
    for (unsigned int i = 0; i < 2*(sudoku._size*sudoku._size + sudoku._size) + 1; ++i)
        os << "-";
    os << std::endl;
    for (unsigned int y = 0; y < sudoku._size*sudoku._size; ++y)
    {
        os << "| ";
        for (unsigned int x = 0; x < sudoku._size*sudoku._size; ++x)
        {
            if (x % sudoku._size == 0 && x != 0)
                os << "| ";
            os << sudoku.getCase(x, y) << " ";
        }
        os << "|" << std::endl;
        if ((y+1) % sudoku._size == 0 && y != 0 && y != sudoku._size*sudoku._size - 1)
        {
            for (unsigned int i = 0; i < 2*(sudoku._size*sudoku._size + sudoku._size) + 1; ++i)
                os << "-";
            os << std::endl;
        }
    }
    for (unsigned int i = 0; i < 2*(sudoku._size*sudoku._size + sudoku._size) + 1; ++i)
        os << "-";
    os << std::endl;
    return os;
}

bool Sudoku::checkElementarySquare(unsigned int x, unsigned int y, unsigned int value) const
{
    unsigned int x0 = x - x % _size;
    unsigned int y0 = y - y % _size;
    for (unsigned int i = 0; i < _size; ++i)
        for (unsigned int j = 0; j < _size; ++j)
            if (getCase(x0 + i, y0 + j) == value)
                return false;
    return true;
}

bool Sudoku::checkLine(unsigned int x, unsigned int y, unsigned int value) const
{
    for (unsigned int i = 0; i < _size*_size; ++i)
        if (getCase(i, y) == value)
            return false;
    return true;
}

bool Sudoku::checkColumn(unsigned int x, unsigned int y, unsigned int value) const
{
    for (unsigned int i = 0; i < _size*_size; ++i)
        if (getCase(x, i) == value)
            return false;
    return true;
}

bool Sudoku::caseIsCorrect(unsigned int x, unsigned int y, unsigned int value) const
{
    return checkElementarySquare(x, y, value) && checkLine(x, y, value) && checkColumn(x, y, value);
}

void Sudoku::generateEmptyGrid()
{
    unsigned int amountToGenerate = (-5*_dificulty+45)*(_size/3)+rand()%5;
    for (unsigned int i = 0; i < amountToGenerate; ++i)
    {
        unsigned int x = rand() % (_size*_size);
        unsigned int y = rand() % (_size*_size);
        unsigned int value = rand() % (_size*_size) + 1;
        if (caseIsCorrect(x, y, value))
            setCase(x, y, value);
        else
            --i;
    }
}
