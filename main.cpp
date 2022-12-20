#include "sudoku.h"

int main()
{
    Sudoku sudoku(1, 3);
    sudoku.genrateStartingGrid();
    std::cout << sudoku << std::endl;
    std::cout << "the sudoku is " << sudoku.isSolved() << "\n";
    // sudoku.solve();
    // std::cout << sudoku << std::endl;

    return EXIT_SUCCESS;
}