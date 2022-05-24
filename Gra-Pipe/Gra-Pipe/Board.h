#ifndef BOARD_H
#define BOARD_H

#include <random>
#include <stack>
#include <tuple>
#include <windows.h>
#include <Utility.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

class Board
{
private:
	int size;
	//2D board matrix of tuples
	std::vector<std::vector<tile>> grid;
public:
	tile& cell(glm::vec2 tile);
	bool isOut(glm::vec2 tile);
	void generate();
	void shuffleBoard();
	void rotate();
	void printBoard();
	Board(int size);
	~Board();
};

#endif
