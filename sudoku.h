#include "grid.h"

class Sudoku
{
public:
    /*!
     *  \brief Constructor.
     *
     *  Default constructor for the sudoku class.
     *
     */
    Sudoku();

    /*!
     *  \brief Constructor.
     *
     *  \param difficulty : Define the amount of case who need to be removed during the generation.
     */
    Sudoku(unsigned int difficulty);

    /*!
     *  \brief Constructor.
     *
     *
     *  \param difficulty : Define the amount of case who need to be removed during the generation.
     *  \param size : The size of the elementary squares.
     */
    Sudoku(unsigned int difficulty, unsigned int size);

    //methods
    /*!
     *  \brief IO overload.
     *
     *  Show the sudoku grid with std::cout.
     *
     */
    friend std::ostream& operator<<(std::ostream& os, const Sudoku& sudoku);

    /*!
     *  \brief Solve the sudoku.

     */
    void solve();

    /*!
     *  \brief Check if the sudoku is solved.
     *  \return Return true if the grid is correct and false otherwise.
     */
    bool isSolved();

    /*!
     *  \brief Allow the user to play the game.
     */
    void playTheGame();

    /*!
     *  \brief Check if the numbers are correctly placed.
     *  \return Return false is a number should not be here.
     */
    bool checkifSudokuIsCorrect();
    long long int getNbIteration();
    std::vector<unsigned int>& getGrid();
    void genrateStartingGrid(bool removeValue);

private:
    //private methods

    /*!
     *  \brief A recursive function who try to solve the sudoku.
     *  \return Return false if the sudoku cant be solved.
     */
    bool backtracking();

    /*!
     *  \brief Place the last number if only one number is missing.
     *  \return Return true if a number was placed this way.
     */
    bool placeRemarquableNumbers();

    /*!
     *  \brief Set x and y to an empty case.
     *  \param x : the x position
     *  \param y : the y position
     *  \return Return true when a case is empty.
     */
    bool caseToBacktrack(unsigned int& x,unsigned int& y);

    /*!
     *  \brief place a number in x,y position.
     *  \param x : the x position
     *  \param y : the y position
     *  \param value : the value to place.
     */
    void setCase(unsigned int x, unsigned int y, unsigned int value);

    /*!
     *  \brief Allow to get the x,y case.
     *  \param x : the x position
     *  \param y : the y position
     *  \return Return value of the case.
     */
    unsigned int getCase(unsigned int x, unsigned int y) const;

    /*!
     *  \brief Check if the numbers respect the row rule.
     *  \param x : the x position
     *  \param y : the y position
     *  \param value : the value to test
     *  \return Return false if the number cant be placed here.
     */
    bool checkRow(unsigned int x, unsigned int y, unsigned int value) const;

    /*!
     *  \brief Check if the numbers respect the column rule.
     *  \param x : the x position
     *  \param y : the y position
     *  \param value : the value to test
     *  \return Return false if the number cant be placed here.
     */
    bool checkColumn(unsigned int x, unsigned int y, unsigned int value) const;

    /*!
     *  \brief Check if the numbers respect the elementary square rule.
     *  \param x : the x position
     *  \param y : the y position
     *  \param value : the value to test
     *  \return Return false if the number cant be placed here.
     */
    bool checkElementarySquare(unsigned int x, unsigned int y, unsigned int value) const;

    /*!
     *  \brief Check if the numbers respect the 3 rules.
     *  \param x : the x position
     *  \param y : the y position
     *  \param value : the value to test
     *  \return Return false if the number cant be placed here.
     */
    bool caseIsCorrect(unsigned int x, unsigned int y, unsigned int value) const;



    //private variables ┬┴┬┴┤ ͜ʖ ͡°) ├┬┴┬┴
    Grid _grid;
    long long int _nbIteration;
};