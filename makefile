ok:
	time g++ -Wall -o Sudoku.out *.cpp
	time ./Sudoku.out

opt:
	time g++ -O -s -Wall -o Sudoku.out *.cpp
	time ./Sudoku.out