#include "Board.h"

//only for tests func
void gotoxy(int x, int y)
{
	COORD c;
	c.X = x - 1;
	c.Y = y - 1;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

Board::Board(int size) {
	this->size = size;
	//initialize boardMatrix's coordinates and mark visited as false
	for (int i = 0; i < size; i++) {
		std::vector<std::tuple<int, int, bool>> temp;
		for (int j = 0; j < size; j++) {
			temp.push_back(std::tuple<int, int, bool>(i, j, false));
		}
		boardMatrix.push_back(temp);
	}
}

Board::~Board() {
	for (auto& i : boardMatrix) {
		i.clear();
	}
	boardMatrix.clear();
}

void Board::generate() {
	srand(time(NULL));

	//set source coordinates & mark first cell as visited
	int x = rand() % size;
	int y = rand() % size;
	this->start_cell = boardMatrix[x][y];
	std::get<0>(start_cell) = x;
	std::get<1>(start_cell) = y;
	std::get<2>(start_cell) = true;
	
	//cell as tuple of <pos_x in boardMatrix, pos_y in boardMatrix, visited>
	std::stack<std::tuple<int, int, bool>> pathStack;
	pathStack.push(start_cell);

	//iterative version of DFS
	while (!pathStack.empty()) {
		std::tuple<int, int, bool> cell = pathStack.top();
		pathStack.pop();
		//neighbour as a tuple of:
		// - pos_x in boardMatrix,
		// - pos_y in boardMatrix,
		// - type of neighbour (top = 1, right = 2, bottom = 4, left = 8) (NESW)
		// - was visited
		
		std::vector<std::tuple<int, int, int, bool>> neighbours = getNeighbours(cell);
		
		if (!neighbours.empty()) {
			//select a random neighbour
			int rnd_idx = rand() % neighbours.size();
			for (int i = 0; i < neighbours.size(); i++) {
				std::get<3>(neighbours[i]) = true;
				if (i != rnd_idx)
					pathStack.push(std::tuple<int, int, bool>(
						std::get<0>(neighbours[i]),
						std::get<1>(neighbours[i]),
						std::get<3>(neighbours[i])));
			}
			pathStack.push(std::tuple<int, int, bool>(
						std::get<0>(neighbours[rnd_idx]),
						std::get<1>(neighbours[rnd_idx]),
						std::get<3>(neighbours[rnd_idx])));

			//connect cell to all neighbours
			connectCell(cell, neighbours);
			printf("%d %d %d\n", std::get<0>(cell), std::get<1>(cell), std::get<2>(cell));
		}
	}
	printf("Board generated\n");
}

std::vector<std::tuple<int, int, int, bool>> Board::getNeighbours(std::tuple<int, int, bool> cell) {
	int x = std::get<0>(cell);
	int y = std::get<1>(cell);
	std::vector<std::tuple<int, int, int, bool>> neighbours;
	neighbours.reserve(4);

	//check if top neighbour is available
	if (x + 1 < this->size && !std::get<2>(boardMatrix[x + 1][y]))
		neighbours.push_back(std::tuple<int, int, int, bool>(x + 1, y, 1, false));
	//check if right neighbour is available
	if (y + 1 < this->size && !std::get<2>(boardMatrix[x][y + 1]))
		neighbours.push_back(std::tuple<int, int, int, bool>(x, y + 1, 2, false));
	//check if bottom neighbour is available
	if (y - 1 >= 0 && !std::get<2>(boardMatrix[x][y - 1]))
		neighbours.push_back(std::tuple<int, int, int, bool>(x, y - 1, 4, false));
	//check if left neighbour is available
	if (x - 1 >= 0 && !std::get<2>(boardMatrix[x - 1][y]))
		neighbours.push_back(std::tuple<int, int, int, bool>(x - 1, y, 8, false));

	//returns a vector of neighbours with their coordinates in boardMatrix
	return neighbours;
}

void Board::connectCell(std::tuple<int, int, bool> cell, std::vector<std::tuple<int, int, int, bool>> neighbours) {
	if (neighbours.size() < 1)
		return;

	for (int i = 0; i < neighbours.size(); i++) {
		int x = std::get<0>(neighbours.at(i));
		int y = std::get<1>(neighbours.at(i));
		int neighbour = std::get<2>(neighbours.at(i));
		bool vis = std::get<3>(neighbours.at(i));
		std::get<0>(boardMatrix[x][y]) = 1;
		std::get<1>(boardMatrix[x][y]) |= neighbour;
		std::get<2>(boardMatrix[x][y]) = vis;
	}
}

void Board::printBoard() {
	int x = 5;
	int y = 5;
	gotoxy(x, y);
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			int value = std::get<1>(boardMatrix[i][j]);
			//gotoxy(x, y);
			printf("%d %d %d\n", i, j, value);
			/*if (value & 1) printf("  |  ");
			else printf("     ");
			gotoxy(x, y+1);
			if (value & 8) printf("--*");
			else printf("  *");
			if (value & 2) printf("--");
			else printf("  ");
			gotoxy(x, y+2);
			if (value & 4) printf("  |  ");
			else printf("     ");
			/*printf("AAAAA");
			gotoxy(x, y + 1);
			printf("BBBBB");
			gotoxy(x, y + 2);
			printf("CCCCC");*/
			x += 5;
		}
		x = 5;
		y += 3;
	}
	printf("\n\n\n\n\n");
}

