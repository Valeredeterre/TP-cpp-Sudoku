//is it a lot ? yes
//is it too mutch ? maybe
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
    void generateEmptyGridWithCasefillInItToPlatTheGameSoItsNotReallyEmpltyWithAnNonWorkingWay();
    void genrateStratingGrid();
    bool solve();
    bool isSolved() const;
    void playTheGame();
    void setCase(unsigned int x, unsigned int y, unsigned int value);

private:

    //private methods
    unsigned int getCase(unsigned int x, unsigned int y) const;
    bool caseIsCorrect(unsigned int x, unsigned int y, unsigned int value) const;
    bool checkElementarySquare(unsigned int x, unsigned int y, unsigned int value) const;
    bool checkLine(unsigned int x, unsigned int y, unsigned int value) const;
    bool checkColumn(unsigned int x, unsigned int y, unsigned int value) const;

    //private variables ┬┴┬┴┤ ͜ʖ ͡°) ├┬┴┬┴
    unsigned int _difficulty;
    unsigned int _size;
    std::vector<unsigned int> _grid;
};