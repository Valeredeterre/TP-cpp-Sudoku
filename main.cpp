#include "sudoku.h"

int main()
{
    Sudoku sudoku(2, 3);
    sudoku.genrateStartingGrid();
    std::cout << sudoku << std::endl;
    sudoku.solve();
    std::cout << sudoku << std::endl;

    return EXIT_SUCCESS;
}