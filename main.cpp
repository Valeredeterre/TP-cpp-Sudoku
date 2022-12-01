#include "sudoku.h"

int main()
{
    Sudoku sudoku(6, 3);
    sudoku.generateEmptyGrid();
    std::cout << sudoku;
    return 0;
}