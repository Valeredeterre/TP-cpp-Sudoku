ok:
	time g++ -Wall -o Sudoku.out *.cpp
	time ./Sudoku.out

opt:
	time g++ -O3 -s -Wall -o Sudoku.out *.cpp
	time ./Sudoku.out