#include "sudoku.h"

int main()
{
    Sudoku sudoku(1, 3);
    sudoku.genrateStartingGrid(true);
    std::cout << sudoku << std::endl;

    sudoku.solve();
    
    std::cout << sudoku << std::endl;
    std::cout << "the sudoku is " << sudoku.isSolved() << "\n";

    return EXIT_SUCCESS;
}