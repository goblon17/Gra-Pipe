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
private:
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
	friend bool checkWin(Board *b);
	void printBoard();
	Board(int size);
	~Board();
};

#endif
