#include "sudoku.h"

int main()
{
    Sudoku sudoku(1, 3);
    sudoku.genrateStratingGrid();
    std::cout << sudoku;

    return 0;
}