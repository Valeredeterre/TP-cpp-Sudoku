#include "sudoku.h"

Sudoku::Sudoku()
    : _difficulty(1), _nbIteration(0)
{
    _grid = Grid(3); // creartion of an grid of 'size' by 'size' squares with an dimention of 'size' by 'size'
}

Sudoku::Sudoku(unsigned int difficulty)
    : _difficulty(difficulty), _nbIteration(0)
{
    _grid = Grid(3); // creartion of an grid of 'size' by 'size' squares with an dimention of 'size' by 'size'
}

Sudoku::Sudoku(unsigned int difficulty, unsigned int size)
    : _difficulty(difficulty), _nbIteration(0)
{
   _grid = Grid(size);
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

void Sudoku::genrateStartingGrid(bool removeValue)
{
    srand(time(NULL)); // initialisation of the randomizer

    // create a valid grid
    int i = 0;
    for (int n = 0; n < pow(_grid.getSize(), 4); n++)
    {
        if (n % (_grid.getSize() * _grid.getSize()) == 0 && n != 0)
            i += _grid.getSize();
        if (n % (_grid.getSize() * _grid.getSize() * _grid.getSize()) == 0 && n != 0)
            i++;
        _grid.getGrid().at(n) = n + i;
    }

    for (int n = 0; n < pow(_grid.getSize(), 4); n++)
    {
        _grid.getGrid().at(n) = _grid.getGrid().at(n) % (_grid.getSize() * _grid.getSize()) + 1;
    }
    shuffleGrid();

    // remove random numbers to match the difficulty
    if (removeValue)
    {
        std::array<float, 6> possibleValue = {0.8, 0.7, 0.6, 0.5, 0.4, 0.3};

        if (_difficulty > 6)
            _difficulty = 6;
        if (_difficulty < 1)
            _difficulty = 1;
        unsigned int amountToGenerate = int(possibleValue.at(_difficulty - 1) * pow(_grid.getSize(), 4));
        for (unsigned int i = 0; i < pow(_grid.getSize(), 4) - amountToGenerate; i++)
        {
            unsigned int x = 0, y = 0;
            do
            {
                x = rand() % (_grid.getSize() * _grid.getSize());
                y = rand() % (_grid.getSize() * _grid.getSize());
            } while (getCase(x, y) == 0);
            setCase(x, y, 0);
        }
    }
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

void Sudoku::swapRows(unsigned int row1, unsigned int row2)
{
    for (unsigned int i = 0; i < _grid.getSize() * _grid.getSize(); ++i)
    {
        unsigned int tmp = getCase(i, row1);
        setCase(i, row1, getCase(i, row2));
        setCase(i, row2, tmp);
    }
}

void Sudoku::swapColumns(unsigned int column1, unsigned int column2)
{
    for (unsigned int i = 0; i < _grid.getSize() * _grid.getSize(); ++i)
    {
        unsigned int tmp = getCase(column1, i);
        setCase(column1, i, getCase(column2, i));
        setCase(column2, i, tmp);
    }
}

void Sudoku::swapValue(unsigned int value1, unsigned int value2)
{
    for (unsigned int i = 0; i < _grid.getSize() * _grid.getSize(); ++i)
    {
        for (unsigned int j = 0; j < _grid.getSize() * _grid.getSize(); ++j)
        {
            if (getCase(i, j) == value1)
                setCase(i, j, value2);
            else if (getCase(i, j) == value2)
                setCase(i, j, value1);
        }
    }
}

void Sudoku::shuffleGrid()
{
    for (int i = 0; i < pow(_grid.getSize(), 5); i++)
    {
        int x1 = rand() % (_grid.getSize() * _grid.getSize());
        int x2 = rand() % (_grid.getSize() * _grid.getSize());

        if ((abs(x1 - x2) < _grid.getSize()) && (x1 != x2) && (x1 / _grid.getSize() == x2 / _grid.getSize()))
        {
            swapRows(x1, x2);
        }
        else if (x1 % _grid.getSize() == x2 % _grid.getSize() && x1 != x2)
        {
            for (unsigned int i = 0; i < _grid.getSize(); ++i)
                swapRows(x1 - x1 % _grid.getSize() + i, x2 - x2 % _grid.getSize() + i);
        }

        x1 = rand() % (_grid.getSize() * _grid.getSize());
        x2 = rand() % (_grid.getSize() * _grid.getSize());

        if ((abs(x1 - x2) < _grid.getSize()) && (x1 != x2) && (x1 / _grid.getSize() == x2 / _grid.getSize()))
        {
            swapColumns(x1, x2);
        }
        else if (x1 % _grid.getSize() == x2 % _grid.getSize() && x1 != x2)
        {
            for (unsigned int i = 0; i < _grid.getSize(); ++i)
                swapColumns(x1 - x1 % _grid.getSize() + i, x2 - x2 % _grid.getSize() + i);
        }

        x1 = rand() % (_grid.getSize() * _grid.getSize()) + 1;
        x2 = rand() % (_grid.getSize() * _grid.getSize()) + 1;

        if (x1 != x2)
        {
            swapValue(x1, x2);
        }
    }
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