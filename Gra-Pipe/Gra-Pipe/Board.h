#ifndef BOARD_H
#define BOARD_H

#include <random>
#include <windows.h>
#include <Utility.h>
#include <glm/glm.hpp>
#include <algorithm>
#include <chrono>

class Board
{
protected:
	int size;
	//2D board matrix of tuples
	tile ***grid;
public:
	void generate();
	std::vector<tile*> getNeighbours(tile *t);
	void dfs(tile *t, int n);
	void setConnections();
	void shuffleBoard();
	void rotate(int n, tile *t);
	bool checkWin();
	void printBoard();
	int getSize();
	tile*** getGrid();
	Board(int size);
	Board() = default;
	~Board();
};

#endif
