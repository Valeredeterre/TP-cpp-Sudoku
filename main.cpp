#include "sudoku.h"

int main()
{
    Sudoku sudoku(4, 3);

    /*std::vector<unsigned int> grilleDeBase = 
    {
        0,0,5,3,0,4,8,0,0,
        9,0,0,0,0,0,0,0,7,
        7,0,0,2,0,9,0,0,4,
        0,0,0,4,0,8,0,0,0,
        0,0,6,0,0,0,3,0,0,
        0,2,9,0,0,0,1,4,0,
        0,0,0,5,4,1,0,0,0,
        0,8,3,0,0,0,2,1,0,
        0,0,0,0,2,0,0,0,0,
    };

    sudoku.getGrid() = grilleDeBase;*/

    std::cout << sudoku << std::endl;

    sudoku.solve();
    
    std::cout << sudoku << std::endl;
    
    std::cout << "the sudoku is " << sudoku.isSolved() << "\n";

    std::cout << sudoku.getNbIteration() << std::endl;

    return EXIT_SUCCESS;
}