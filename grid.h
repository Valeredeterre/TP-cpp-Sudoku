#include <iostream>
#include <string>
#include <vector>
#include <array>
#include <cmath>
#include <time.h>
#include <stdlib.h>

class Grid
{
public:
    Grid(unsigned int size = 3);
    friend std::ostream& operator<<(std::ostream& os, const Grid& grid);
    unsigned int getCase(unsigned int x, unsigned int y) const;
    void setCase(unsigned int x, unsigned int y, unsigned int value);
    void at(unsigned int n);
    std::vector<unsigned int>& getGrid();
private:
    unsigned int _size;
    std::vector<unsigned int> _grid;
};