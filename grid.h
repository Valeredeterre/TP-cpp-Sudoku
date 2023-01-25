#include <iostream>
#include <string>
#include <vector>
#include <array>
#include <algorithm>
#include <cmath>
#include <time.h>
#include <stdlib.h>

class Grid
{
public:
    //constructor
    /*!
     *  \brief Default constructor of the Grid class.
     *  \param difficulty : Define the amount of case who need to be removed during the generation.
     *  \param size : The size of the elementary squares.
     */
    Grid(unsigned int size = 3, unsigned int difficulty = 3);

    //methods
    /*!
     *  \brief Getter for the _size attribute.
     *  \return Return the size if the grid.
     */
    unsigned int getSize() const;

    /*!
     *  \brief Getter for the difficulty attribute.
     *  \return Return the size if the grid.
     */
    unsigned int getDifficulty() const;

    std::vector<unsigned int>& getGrid();
    void generateStartingGrid(bool removeValue);
    unsigned int getCase(unsigned int x, unsigned int y) const;
    void setCase(unsigned int x, unsigned int y, unsigned int value);
    friend std::ostream& operator<<(std::ostream& os, const Grid& grid);
    unsigned int lastMissingNumber(unsigned int x, unsigned int y) const;

private:
    //private methods
    void shuffleGrid();
    void swapRows(unsigned int row1, unsigned int row2);
    void swapValue(unsigned int value1, unsigned int value2);
    void swapColumns(unsigned int column1, unsigned int column2);
    unsigned int lastMissingInRow(unsigned int y) const;
    unsigned int lastMissingInColumn(unsigned int x) const;
    unsigned int lastMissingInSquare(unsigned int x, unsigned int y) const;

    //private variables
    std::vector<unsigned int> _grid;
    const unsigned int _difficulty;
    const unsigned int _size;
};