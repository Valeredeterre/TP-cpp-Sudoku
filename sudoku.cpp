#include "sudoku.h"

Sudoku::Sudoku()
    : _difficulty(1), _size(3)
{
    Grid _grid(3); // creartion of an grid of 'size' by 'size' squares with an dimention of 'size' by 'size'
}

Sudoku::Sudoku(unsigned int difficulty)
    : _difficulty(difficulty), _size(3)
{
    Grid _grid(_size); // creartion of an grid of 'size' by 'size' squares with an dimention of 'size' by 'size'
}

Sudoku::Sudoku(unsigned int difficulty, unsigned int size)
    : _difficulty(difficulty), _size(size)
{
    Grid _grid(_size);
}

unsigned int Sudoku::getCase(unsigned int x, unsigned int y) const
{
    return _grid.getCase(x, y); // return the case using an x,y coordonate system instead of an all the number in line one
}

void Sudoku::setCase(unsigned int x, unsigned int y, unsigned int value)
{
    _grid.setCase(x, y, value); // set the case using an x,y coordonate system instead of an all the number in line one
}

std::ostream &operator<<(std::ostream &os, const Sudoku &sudoku) // << overload to print the grid
{
    std::cout << sudoku._grid << std::endl;
    return os;
}

bool Sudoku::checkElementarySquare(unsigned int x, unsigned int y, unsigned int value) const
{
    unsigned int xStartElementarySquare = x - x % _size; // find the coordonate of the elementary square
    unsigned int yStartElementarySquare = y - y % _size;
    for (unsigned int i = 0; i < _size; ++i)
        for (unsigned int j = 0; j < _size; ++j)
            if (getCase(xStartElementarySquare + i, yStartElementarySquare + j) == value)
                return false; // if the case we want to add is already in the square we return false
    return true;
}

bool Sudoku::checkLine(unsigned int x, unsigned int y, unsigned int value) const
{
    for (unsigned int i = 0; i < _size * _size; ++i)
        if (getCase(i, y) == value)
            return false; // if the case we want to add is already in the line we return false
    return true;
}

bool Sudoku::checkColumn(unsigned int x, unsigned int y, unsigned int value) const
{
    for (unsigned int i = 0; i < _size * _size; ++i)
        if (getCase(x, i) == value)
            return false; // if the case we want to add is already in the column we return false
    return true;
}

bool Sudoku::caseIsCorrect(unsigned int x, unsigned int y, unsigned int value) const
{
    return checkElementarySquare(x, y, value) && checkLine(x, y, value) && checkColumn(x, y, value) && (getCase(x, y) == 0);
    // if the 3 sudoku rules are respected and the case is emplty we can add the case here
}

void Sudoku::genrateStartingGrid()
{
    srand(time(NULL)); // initialisation of the randomizer

    // create a valid grid
    int i = 0;
    for (int n = 0; n < pow(_size, 4); n++)
    {
        if (n % (_size * _size) == 0 && n != 0)
            i += _size;
        if (n % (_size*_size*_size) == 0 && n != 0)
            i++;
        _grid.getGrid().at(n) = n + i;
    }

    for (int n = 0; n < pow(_size, 4); n++)
    {
        _grid.getGrid().at(n) = _grid.getGrid().at(n) % (_size * _size) + 1;
    }

    shuffleGrid();

    // remove random numbers to match the difficulty
    std::array<int, 6> possibleValue = {50, 45, 40, 35, 30, 25};
    if (_difficulty > 6)
        _difficulty = 6;
    if (_difficulty < 1)
        _difficulty = 1;
    unsigned int amountToGenerate = possibleValue.at(_difficulty - 1)*pow(_size/3, 3);
    for (unsigned int i = 0; i < pow(_size,4) - amountToGenerate; i++)
    {
        unsigned int x = 0, y = 0;
        do
        {
            x = rand() % (_size * _size);
            y = rand() % (_size * _size);
        }
        while (getCase(x, y) == 0);
        setCase(x, y, 0);
    }
}

void Sudoku::playTheGame() //! not usefull and coded awfully but it's fun
{
    int x, y, value;
    do
    {
        std::cout << std::endl<< *this << std::endl;
        do
        {
            do
            {
                std::cout << "Enter x: ";
                std::cin >> x;
                std::cout << std::endl;
            } while (!(x >= 0 && x < 9));
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
    bool full = true;
    for (auto i : _grid.getGrid())
        if (i == 0)
            return false;
    return checkifSudokuIsCorrect();
}

bool Sudoku::checkifSudokuIsCorrect()
{
    for (unsigned int i = 0; i < _size * _size; ++i)
    {
        for (unsigned int j = 0; j < _size * _size; ++j)
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

void Sudoku::swapLines(unsigned int line1, unsigned int line2)
{
    for (unsigned int i = 0; i < _size * _size; ++i)
    {
        int tmp = getCase(i, line1);
        setCase(i, line1, getCase(i, line2));
        setCase(i, line2, tmp);
    }
}

void Sudoku::swapColumns(unsigned int column1, unsigned int column2)
{
    for (unsigned int i = 0; i < _size * _size; ++i)
    {
        int tmp = getCase(column1, i);
        setCase(column1, i, getCase(column2, i));
        setCase(column2, i, tmp);
    }
}

void Sudoku::shuffleGrid()
{
    int sc = 0;
    int sl = 0;
    for(int i = 0; i < pow(_size, 4); i++)
    {
        int x1 = rand() % (_size * _size);
        int x2 = rand() % (_size * _size);
        bool correct = abs(x1 - x2) < _size;

        if(rand() % 1 == 0 && correct)
        {
            swapLines(x1, x2);
            sl++;
        }
        else
        {   
            swapColumns(x1, x2);
            sc++;
        }
    }
    std::cout << "swaped lines: " << sl << std::endl;
    std::cout << "swaped columns: " << sc << std::endl;
}

bool Sudoku::placeRemarquableNumbers()
{
    for(auto it : _grid.getGrid())
    {
        if (it == 0)
        {

        }
    }
    return false;
}

bool Sudoku::solve()
{
    do {} while (placeRemarquableNumbers());
    if (isSolved())
        return true;
    else
        return false;
}


