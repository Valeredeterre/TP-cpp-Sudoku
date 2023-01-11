#include "sudoku.h"

int main()
{
    Sudoku sudoku(6, 5);
    sudoku.genrateStartingGrid(true);
    std::cout << sudoku << std::endl;

    sudoku.backtracking();
    
    std::cout << sudoku << std::endl;
    std::cout << "the sudoku is " << sudoku.isSolved() << "\n";

    std::cout << sudoku.getNbIteration() << std::endl;

    return EXIT_SUCCESS;
}