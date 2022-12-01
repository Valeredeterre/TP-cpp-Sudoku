#include "sudoku.h"

Sudoku::Sudoku()
: _difficulty(1), _size(3)
{
    srand(time(nullptr)); //initialisation of the randomizer
    _grid.resize(pow(_size, 4)); //creartion of an grid of 'size' square of 'size' by 'size' 
}

Sudoku::Sudoku(unsigned int difficulty)
: _difficulty(difficulty), _size(3)
{
    srand(time(nullptr));
    _grid.resize(pow(_size, 4));
}

Sudoku::Sudoku(unsigned int difficulty, unsigned int size)
: _difficulty(difficulty), _size(size)
{
    srand(time(nullptr));
    _grid.resize(pow(_size, 4));
}

unsigned int Sudoku::getCase(unsigned int x, unsigned int y) const
{
    return _grid.at(y * _size + x); // return the case using an x,y coordonate system instead of an all the number in line one
}

void Sudoku::setCase(unsigned int x, unsigned int y, unsigned int value)
{
    _grid.at(y * _size + x) = value; //set the case using an x,y coordonate system instead of an all the number in line one
}

//TODO : manage the high number for the grid with size > 3 
std::ostream& operator<<(std::ostream& os, const Sudoku& sudoku) // << overload the print the grid
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

            int caseValue = sudoku.getCase(x, y);
            caseValue==0?os<<". ":os<<caseValue<<" ";
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
    unsigned int xStartElementarySquare = x - x % _size; // find the coordonate of the elementary square
    unsigned int yStartElementarySquare = y - y % _size;
    for (unsigned int i = 0; i < _size; ++i)
        for (unsigned int j = 0; j < _size; ++j)
            if (getCase(xStartElementarySquare + i, yStartElementarySquare + j) == value)
                return false; //if the case we want to add is already in the square we return false
    return true;
}

bool Sudoku::checkLine(unsigned int x, unsigned int y, unsigned int value) const
{
    for (unsigned int i = 0; i < _size*_size; ++i)
        if (getCase(i, y) == value)
            return false;  //if the case we want to add is already in the line we return false
    return true;
}

bool Sudoku::checkColumn(unsigned int x, unsigned int y, unsigned int value) const
{
    for (unsigned int i = 0; i < _size*_size; ++i)
        if (getCase(x, i) == value)
            return false;  //if the case we want to add is already in the column we return false
    return true;
}

bool Sudoku::caseIsCorrect(unsigned int x, unsigned int y, unsigned int value) const
{
    return checkElementarySquare(x, y, value) && checkLine(x, y, value) && checkColumn(x, y, value) && (getCase(x, y) == 0);
    // if the 3 sudoku rules are respected and the case is emplty we can add the case here
}

void Sudoku::generateEmptyGrid() // ! WORK BUT ONLY WHEN THE MOON, THE SUN AND JUPITER ARE ALIGNED and dont do exacly what I want (╯’□’)╯︵ ┻━┻ ....
{
    // unsigned int amountToGenerate = (-5*_difficulty+45)*(_size/3)+rand()%5;
    std::array<int, 6> possibleValue = {50, 45, 40, 35, 30, 25};
    if (_difficulty > 6)
        _difficulty = 6;
    if (_difficulty < 1)
        _difficulty = 1;
    // unsigned int amountToGenerate = possibleValue.at(_difficulty-1);
    unsigned int amountToGenerate = 3;

    std::cout << amountToGenerate << "\n";
    for (unsigned int i = 0; i < amountToGenerate; i++)
    {
        unsigned int x = 0, y = 0, value = 0;
        do
        {
            x = rand() % (_size * _size);
            y = rand() % (_size * _size);
            value = rand() % (_size * _size) + 1;

        } while (!caseIsCorrect(x, y, value));
        std::cout << i << "\n";
        setCase(x, y, value);
    }
}

// void Sudoku::generateEmptyGrid() //! cancel due to brain overload but at the end it's supposed to work
//! for the next method https://stackoverflow.com/questions/6924216/how-to-generate-sudoku-boards-with-unique-solutions#:~:text=Start%20with%20a%20complete%2C%20valid,using%20a%20fast%20backtracking%20solver.
// {
//     std::vector<std::vector<unsigned int>> horizontalLines;
//     for(unsigned int i = 0; i < _size*_size; i++)
//     {
//         for(unsigned int j = 0; j < _size*_size; j++)
//         {
//             horizontalLines.at(i).push_back(0);
//         }
//     }
// }

//TODO: 
//? just check if it's full or check if it's right? (maybe add the caseIsCorrect method in the get case method to do that)  
bool Sudoku::isSolved()
{

}