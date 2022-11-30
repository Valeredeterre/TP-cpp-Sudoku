
#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <time.h>
#include <stdlib.h>

class Sudoku
{
public:
    Sudoku();
    Sudoku(unsigned int dificulty);
    Sudoku(unsigned int dificulty, unsigned int size);
    unsigned int getCase(unsigned int x, unsigned int y) const;
    void setCase(unsigned int x, unsigned int y, unsigned int value);
    friend std::ostream& operator<<(std::ostream& os, const Sudoku& sudoku);
    void generateEmptyGrid();
private:
    bool caseIsCorrect(unsigned int x, unsigned int y, unsigned int value) const;
    bool checkElementarySquare(unsigned int x, unsigned int y, unsigned int value) const;
    bool checkLine(unsigned int x, unsigned int y, unsigned int value) const;
    bool checkColumn(unsigned int x, unsigned int y, unsigned int value) const;
    unsigned int _dificulty;
    unsigned int _size;
    std::vector<unsigned int> _grid;
};