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
     *  \return Return the size of the grid.
     */
    unsigned int getSize() const;

    /*!
     *  \brief Getter for the difficulty attribute.
     *  \return Return the difficulty of the grid.
     */
    unsigned int getDifficulty() const;

    /*!
     *  \brief Getter for the _grid attribute.
     *  \return Return the grid.
     */
    std::vector<unsigned int>& getGrid();

    /*!
     *  \brief This function generate a random grid of sudoku and remove an amount of values depending of the difficulty.
     *  \param removeValue : If this parameter is set to false the grid will be generated but value will not be removed.
     */
    void generateStartingGrid(bool removeValue);

    /*!
     *  \brief Setter who translate the 1d grid into a 2d grid.
     *  \param x : the x position
     *  \param y : the y position
     *  \return return the value on the case
     */
    unsigned int getCase(unsigned int x, unsigned int y) const;

    /*!
     *  \brief Setter who the 1d grid into a 2d grid.
     *  \param x : the x position
     *  \param y : the y position
     *  \param value : The value to place.
     */
    void setCase(unsigned int x, unsigned int y, unsigned int value);

    /*!
     *  \brief IO overload.
     *
     *  Show the sudoku grid with std::cout.
     *
     */
    friend std::ostream& operator<<(std::ostream& os, const Grid& grid);

    /*!
     *  \brief Allow to get the lass value possible in a case.
     *  \param x : the x position
     *  \param y : the y position
     *  \return Return a 0 if multiple values are allowed in this case and the only value otherwise.
     */
    unsigned int lastMissingNumber(unsigned int x, unsigned int y) const;

private:
    //private methods
    void shuffleGrid();

    /*!
    *  \brief Swap two rows to shuffle the grid
    *  \param row1 : the first row coordinate
    *  \param row2 : the second row coordinate
    */
    void swapRows(unsigned int row1, unsigned int row2);

    /*!
     *  \brief Swap two values to shuffle the grid
     *  \param value1 : the first value
     *  \param value2 : the second value
     */
    void swapValue(unsigned int value1, unsigned int value2);

    /*!
     *  \brief Swap two column to shuffle the grid
     *  \param row1 : the first column coordinate
     *  \param row2 : the second column coordinate
     */
    void swapColumns(unsigned int column1, unsigned int column2);
    unsigned int lastMissingInRow(unsigned int y) const;
    unsigned int lastMissingInColumn(unsigned int x) const;
    unsigned int lastMissingInSquare(unsigned int x, unsigned int y) const;

    //private variables
    std::vector<unsigned int> _grid;
    unsigned int _difficulty;
    unsigned int _size;
};