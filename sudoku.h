
#include <iostream>
#include <string>
#include <vector>
#include <array>
#include <cmath>
#include <time.h>
#include <stdlib.h>

class Sudoku
{
public:
    //constructors
    Sudoku();
    Sudoku(unsigned int difficulty);
    Sudoku(unsigned int difficulty, unsigned int size);

    //methods
    friend std::ostream& operator<<(std::ostream& os, const Sudoku& sudoku);
    void generateEmptyGrid();

private:

    //private methods
    unsigned int getCase(unsigned int x, unsigned int y) const;
    void setCase(unsigned int x, unsigned int y, unsigned int value);
    bool caseIsCorrect(unsigned int x, unsigned int y, unsigned int value) const;
    bool checkElementarySquare(unsigned int x, unsigned int y, unsigned int value) const;
    bool checkLine(unsigned int x, unsigned int y, unsigned int value) const;
    bool checkColumn(unsigned int x, unsigned int y, unsigned int value) const;

    //private variables ┬┴┬┴┤ ͜ʖ ͡°) ├┬┴┬┴
    unsigned int _difficulty;
    unsigned int _size;
    std::vector<unsigned int> _grid;
    bool isSolved();
};