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
}

Board::~Board() {
	for (auto& i : grid) {
		i.clear();
	}
	grid.clear();
}

tile& Board::cell(glm::vec2 tile) {
	return grid[(int) tile.x][(int) tile.y];
}

bool Board::isOut(glm::vec2 tile) {
	for (int i = 1; i < this->size - 1; i++)
		for (int j = 1; j < this->size - 1; j++)
			if (i == tile.x && j == tile.y)
				return false;
	return true;
}

void Board::generate() {
	std::mt19937 mt(NULL);

	std::vector<glm::vec2> nodes;
	nodes.push_back(glm::vec2(mt() % this->size, mt() % this->size));

	while (!nodes.empty()) {
		int n = mt() % nodes.size();
		glm::vec2 v = nodes[n];
		glm::vec2 d = directions[mt() % 4];

		if (cell(v).dirs.size() == 3) {
			nodes.erase(nodes.begin() + n);
			continue;
		}
		if (cell(v).dirs.size() == 2)
			if (mt() % 2)
				continue;

		bool complete = 1;
		for (auto dir : directions)
			if (!isOut(v + dir) && cell(v + dir).dirs.empty())
				complete = 0;
		if (complete) {
			nodes.erase(nodes.begin() + n);
			continue;
		}

		if (isOut(v + d))
			continue;
		if (!cell(v + d).dirs.empty())
			continue;
		cell(v).dirs.push_back(d);
		cell(v + d).dirs.push_back(-d);
		nodes.push_back(v + d);
	}

	printf("Board generated\n");
}


void Board::printBoard() {
	int x = 5;
	int y = 5;
	gotoxy(x, y);
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			for (auto k : grid[i][j].dirs)
				printf("%d %d\n", (int) k.x, (int) k.y);
			/*gotoxy(x, y);
			//printf("%d %d %d %d\n", i, j, boardMatrix[i][j].connected, value);
			//printf("% d", boardMatrix[i][j].connected);
			if (value & 1) printf("  |  ");
			else printf("     ");
			gotoxy(x, y+1);
			if (value & 8) printf("--*");
			else printf("  *");
			if (value & 2) printf("--");
			else printf("  ");
			gotoxy(x, y+2);
			if (value & 4) printf("  |  ");
			else printf("     ");
			x += 5;*/
		}
		x = 5;
		y += 3;
	}
	printf("\n\n\n\n\n");
}

