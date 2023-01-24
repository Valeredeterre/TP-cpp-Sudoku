#include "sudoku.h"

Sudoku::Sudoku()
    : _nbIteration(0)
{
    _grid = Grid(); // creartion of a grid of 'size' by 'size' squares with a dimention of 'size' by 'size'
    _grid.generateStartingGrid(true);
}

Sudoku::Sudoku(unsigned int difficulty)
    : _nbIteration(0)
{
    _grid = Grid(3, difficulty); // creartion of a grid of 'size' by 'size' squares with a dimention of 'size' by 'size'
    _grid.generateStartingGrid(true);
}

Sudoku::Sudoku(unsigned int difficulty, unsigned int size)
    : _nbIteration(0)
{
   _grid = Grid(size, difficulty);
   _grid.generateStartingGrid(true);
}

std::vector<unsigned int>& Sudoku::getGrid()
{
    return _grid.getGrid();
}

unsigned int Sudoku::getCase(unsigned int x, unsigned int y) const
{
    return _grid.getCase(x, y); // return the case using an x,y coordonate system instead of an all the number in row one
}

void Sudoku::setCase(unsigned int x, unsigned int y, unsigned int value)
{
    _grid.setCase(x, y, value); // set the case using an x,y coordonate system instead of an all the number in row one
}

std::ostream &operator<<(std::ostream &os, const Sudoku &sudoku) // << overload to print the grid
{
    std::cout << sudoku._grid << std::endl;
    return os;
}

bool Sudoku::checkElementarySquare(unsigned int x, unsigned int y, unsigned int value) const
{
    unsigned int xStartElementarySquare = x - x % _grid.getSize(); // find the coordonate of the elementary square
    unsigned int yStartElementarySquare = y - y % _grid.getSize();
    for (unsigned int i = 0; i < _grid.getSize(); ++i)
        for (unsigned int j = 0; j < _grid.getSize(); ++j)
            if (getCase(xStartElementarySquare + i, yStartElementarySquare + j) == value)
                return false; // if the case we want to add is already in the square we return false
    return true;
}

bool Sudoku::checkRow(unsigned int x, unsigned int y, unsigned int value) const
{
    for (unsigned int i = 0; i < _grid.getSize() * _grid.getSize(); ++i)
        if (getCase(i, y) == value)
            return false; // if the case we want to add is already in the row we return false
    return true;
}

bool Sudoku::checkColumn(unsigned int x, unsigned int y, unsigned int value) const
{
    for (unsigned int i = 0; i < _grid.getSize() * _grid.getSize(); ++i)
        if (getCase(x, i) == value)
            return false; // if the case we want to add is already in the column we return false
    return true;
}

bool Sudoku::caseIsCorrect(unsigned int x, unsigned int y, unsigned int value) const
{
    return checkElementarySquare(x, y, value) && checkRow(x, y, value) && checkColumn(x, y, value) && (getCase(x, y) == 0);
    // if the 3 sudoku rules are respected and the case is emplty we can add the case here
}

void Sudoku::playTheGame() //! not usefull and coded awfully but it's fun
{
    unsigned int x, y, value;
    do
    {
        std::cout << std::endl
                  << *this << std::endl;
        do
        {
            do
            {
                std::cout << "Enter x: ";
                std::cin >> x;
                std::cout << std::endl;
            } while (!(x >= 0 && x < _grid.getSize() * _grid.getSize()));
            do
            {
                std::cout << "Enter y: ";
                std::cin >> y;
                std::cout << std::endl;
            } while (!(y >= 0 && y < 9));
            do
            {
                std::cout << "Enter value: ";
                std::cin >> value;
                std::cout << std::endl;
            } while (!(value >= 0 && value < 9));
        } while (getCase(x, y) != 0);
        setCase(x, y, value);
    } while (!isSolved());
}

bool Sudoku::isSolved()
{
    for (auto i : _grid.getGrid())
        if (i == 0)
            return false;
    return checkifSudokuIsCorrect();
}

bool Sudoku::checkifSudokuIsCorrect()
{
    for (unsigned int i = 0; i < _grid.getSize() * _grid.getSize(); ++i)
    {
        for (unsigned int j = 0; j < _grid.getSize() * _grid.getSize(); ++j)
        {
            int tmp = getCase(i, j);
            setCase(i, j, 0);
            if (!caseIsCorrect(i, j, tmp))
                return false;
            setCase(i, j, tmp);
        }
    }
    return true;
}



bool Sudoku::placeRemarquableNumbers()
{
    unsigned int missing = _grid.lastMissingNumber(0, 0);
    for (unsigned int x = 0; x < _grid.getSize() * _grid.getSize(); x++)
    {
        for (unsigned int y = 0; y < _grid.getSize() * _grid.getSize(); y++)
        {
            missing = _grid.lastMissingNumber(x, y);
            if (getCase(x, y) == 0 && missing != 0)
            {
                setCase(x, y, missing);
                return true;
            }
        }
    }
    return false;
}

void Sudoku::solve()
{
    while (placeRemarquableNumbers() && !isSolved());
    backtracking();
}

long long int Sudoku::getNbIteration()
{
    return _nbIteration;
}

bool Sudoku::caseToBacktrack(unsigned int &x, unsigned int &y)
{
    for (x = 0; x < _grid.getSize() * _grid.getSize(); x++)
    {
        for (y = 0; y < _grid.getSize() * _grid.getSize(); y++)
        {
            if (getCase(x, y) == 0)
                return true;
        }
    }
    return false;
}

bool Sudoku::backtracking()
{
    _nbIteration++;
    unsigned int x = 0;
    unsigned int y = 0;
    if (!caseToBacktrack(x, y))
        return true;

    if (_nbIteration % 100000  == 0)
        std::cout << ".";
    if (_nbIteration % 5000000 == 0)
        std::cout << "\n" << _nbIteration << " iterations";

    for (unsigned int i = 1; i <= _grid.getSize() * _grid.getSize(); i++)
    {
        if (caseIsCorrect(x, y, i))
        {
            setCase(x, y, i);
            if (backtracking())
                return true;
            setCase(x, y, 0);
        }
    }
    return false;
}