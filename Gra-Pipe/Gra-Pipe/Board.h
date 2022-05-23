#ifndef BOARD_H
#define BOARD_H

#include <random>
#include <stack>
#include <tuple>
#include <windows.h>

class Board
{
private:
	int size;
	//2D board matrix of tuples
	std::vector<std::vector<std::tuple<int, int, bool>>> boardMatrix;
	//cell as tuple of <connect flag, value (0000), visited>
	std::tuple<int, int, bool> start_cell;
public:
	void generate();
	std::vector<std::tuple<int, int, int, bool>> getNeighbours(std::tuple<int, int, bool> cell);
	void connectCell(std::tuple<int, int, bool> cell, std::vector<std::tuple<int, int, int, bool>> neighbours);
	void shuffleBoard();
	void rotate();
	void printBoard();
	Board(int size);
	~Board();
};

#endif
