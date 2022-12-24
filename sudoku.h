#include "grid.h"

class Sudoku
{
public:
    //constructors
    Sudoku();
    Sudoku(unsigned int difficulty);
    Sudoku(unsigned int difficulty, unsigned int size);

    //methods
    friend std::ostream& operator<<(std::ostream& os, const Sudoku& sudoku);
    
    void genrateStartingGrid(bool removeValue);
    void solve();
    bool isSolved();
    void playTheGame();
    bool checkifSudokuIsCorrect();
    void setCase(unsigned int x, unsigned int y, unsigned int value);

private:
    //private methods
    unsigned int getCase(unsigned int x, unsigned int y) const;
    bool caseIsCorrect(unsigned int x, unsigned int y, unsigned int value) const;
    bool checkElementarySquare(unsigned int x, unsigned int y, unsigned int value) const;
    bool checkRow(unsigned int x, unsigned int y, unsigned int value) const;
    bool checkColumn(unsigned int x, unsigned int y, unsigned int value) const;
    void swapColumns(unsigned int column1, unsigned int column2);
    void swapRows(unsigned int row1, unsigned int row2);
    void swapValue(unsigned int value1, unsigned int value2);
    void shuffleGrid();
    bool placeRemarquableNumbers();
    bool backtracking();
    void solveLikeAPersonWouldDoOnAnEasyOne();

    //private variables ┬┴┬┴┤ ͜ʖ ͡°) ├┬┴┬┴
    unsigned int _difficulty;
    unsigned int _size;
    Grid _grid;
};