#include "sudoku.h"

int main()
{
    Sudoku sudoku(6);
    sudoku.generateEmptyGrid();
    std::cout << sudoku;
}