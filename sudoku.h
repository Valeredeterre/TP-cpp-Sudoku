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
    
    void solve();
    bool isSolved();
    void playTheGame();
    bool checkifSudokuIsCorrect();
    long long int getNbIteration();
    std::vector<unsigned int>& getGrid();
    void genrateStartingGrid(bool removeValue);
    void setCase(unsigned int x, unsigned int y, unsigned int value);

private:
    //private methods
    void shuffleGrid();
    bool backtracking();
    bool placeRemarquableNumbers();
    bool caseToBacktrack(unsigned int& x,unsigned int& y);
    unsigned int getCase(unsigned int x, unsigned int y) const;
    bool checkRow(unsigned int x, unsigned int y, unsigned int value) const;
    bool checkColumn(unsigned int x, unsigned int y, unsigned int value) const;
    bool caseIsCorrect(unsigned int x, unsigned int y, unsigned int value) const;
    bool checkElementarySquare(unsigned int x, unsigned int y, unsigned int value) const;

    //private variables ┬┴┬┴┤ ͜ʖ ͡°) ├┬┴┬┴
    Grid _grid;
    long long int _nbIteration;
};