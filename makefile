ok:
	g++ -Wall -o Sudoku.out *.cpp
	time ./Sudoku.out

opt:
	g++ -O3 -s -Wall -o Sudoku.out *.cpp
	time ./Sudoku.out