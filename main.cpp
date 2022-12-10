#include "sudoku.h"

int main()
{
    Sudoku sudoku(5, 7);
    sudoku.genrateStartingGrid();
    std::cout << sudoku;
    std::cout << "Sudoku is " << (sudoku.checkifSudokuIsCorrect() ? "correct" : "incorrect") << std::endl;

    return 0;
}