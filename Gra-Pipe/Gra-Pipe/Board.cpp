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
	this->grid = new tile** [this->size];
	for (int i = 0; i < this->size; i++) {
		this->grid[i] = new tile* [this->size];
		for (int j = 0; j < this->size; j++) {
			this->grid[i][j] = new tile(i, j, 0, 0);
		}
	}
}

Board::~Board() {
	for (int i = 0; i < this->size; i++) {
		for (int j = 0; j < this->size; j++)
			delete this->grid[i][j];
		delete this->grid[i];
	}
	delete this->grid;
}

void Board::generate() {
	dfs(this->grid[0][0], 0);

	printf("Board generated\n");
	this->setConnections();
}

std::vector<tile*> Board::getNeighbours(tile *t) {
	std::vector<tile*> neighbours;
	neighbours.reserve(4);

	unsigned seed = (unsigned) std::chrono::system_clock::now().time_since_epoch().count();
	std::mt19937 mt(seed);
	seed = mt();

	std::default_random_engine e(seed);

	// top neighbour
	if (t->x - 1 >= 0)
		neighbours.push_back(this->grid[t->x - 1][t->y]);
	// left neighbour
	if (t->y - 1 >= 0)
		neighbours.push_back(this->grid[t->x][t->y - 1]);
	// bottom neighbour
	if (t->x + 1 < this->size)
		neighbours.push_back(this->grid[t->x + 1][t->y]);
	// right neighbour
	if (t->y + 1 < this->size)
		neighbours.push_back(this->grid[t->x][t->y + 1]);

	std::shuffle(neighbours.begin(), neighbours.end(), e);
	
	return neighbours;
}

void Board::dfs(tile *t, int n) {
	t->visited = true;
	t->currentValue = n;
	for (tile* i : getNeighbours(t)) {
		if (!i->visited)
			dfs(i, n + 1);
	}
}

void Board::setConnections() {
	for (int i = 0; i < this->size; i++) {
		for (int j = 0; j < this->size; j++) {
			tile* current = this->grid[i][j];
			std::vector<tile*> neighbours = this->getNeighbours(current);
			for (auto k : neighbours) {
				if(abs((int) k->currentValue - (int) current->currentValue) != 1)
					continue;
				//add top connection
				if (k->x == current->x - 1) current->correctValue |= 1;
				//add bottom connection
				if (k->x == current->x + 1) current->correctValue |= 4;
				//add left connection
				if (k->y == current->y - 1) current->correctValue |= 8;
				//add right connection
				if (k->y == current->y + 1) current->correctValue |= 2;
			}
			if ((current->correctValue & current->correctValue - 1) == 0)
				current->isTarget = true;
		}
	}

	for (int i = 0; i < this->size; i++)
		for (int j = 0; j < this->size; j++)
			this->grid[i][j]->currentValue = this->grid[i][j]->correctValue;

	int x = rand() % this->size;
	int y = rand() % this->size;
	this->grid[x][y]->isSource = true;
	this->grid[x][y]->isTarget = false;
}

void Board::shuffleBoard() {
	for (int i = 0; i < this->size; i++)
		for (int j = 0; j < this->size; j++) 
			rotate(rand() % 3 + 1, this->grid[i][j]);
}

void Board::rotate(int n, tile* t) {
	for (int i = 0; i < n; i++) {
		if (!(t->currentValue % 2))
			t->currentValue = t->currentValue / 2.0;
		else
			t->currentValue = t->currentValue / 2.0 + 7.5;
	}
}

void Board::printBoard() {
	int x = 2;
	int y = 4;

	gotoxy(2, 2);
	printf("Correct Board:");
	gotoxy(this->size * 5 + 4, 2);
	printf("Current Board:");
	for (int i = 0; i < this->size; i++) {
		for (int j = 0; j < this->size; j++) {
			int type = this->grid[i][j]->correctValue;
			gotoxy(x + 2, y + 1);
			if (this->grid[i][j]->isTarget) printf("O");
			else if (this->grid[i][j]->isSource) printf("S");
			else printf("*");
			
			if (type & 1) { gotoxy(x + 2, y); printf("|"); }
			if (type & 2) { gotoxy(x + 3, y + 1); printf("--"); }
			if (type & 4) { gotoxy(x + 2, y + 2); printf("|"); }
			if (type & 8) { gotoxy(x, y + 1); printf("--"); }
			x += 5;
		}
		printf("\n");
		x = 2;
		y += 3;
	}
	
	
	x = this->size * 5 + 4;
	y = 4;
	for (int i = 0; i < this->size; i++) {
		for (int j = 0; j < this->size; j++) {
			int type = this->grid[i][j]->currentValue;
			gotoxy(x + 2, y + 1);
			if (this->grid[i][j]->isTarget) printf("O");
			else if (this->grid[i][j]->isSource) printf("S");
			else printf("*");

			if (type & 1) { gotoxy(x + 2, y); printf("|"); }
			if (type & 2) { gotoxy(x + 3, y + 1); printf("--"); }
			if (type & 4) { gotoxy(x + 2, y + 2); printf("|"); }
			if (type & 8) { gotoxy(x, y + 1); printf("--"); }
			x += 5;
		}
		printf("\n");
		x = this->size * 5 + 4;
		y += 3;
	}
	printf("\n\n");
}

bool checkWin(Board *b) {
	for (int i = 0; i < b->size; i++)
		for (int j = 0; j < b->size; j++)
			if (b->grid[i][j]->correctValue != b->grid[i][j]->currentValue)
				return false;
	return true;
}

int Board::getSize() {
	return this->size;
}

tile*** Board::getGrid() {
	return this->grid;
}
