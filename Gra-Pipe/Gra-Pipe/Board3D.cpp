#include "Board3D.h"

Board3D::Board3D(int size) : Board(size) {
	this->model_board = new TileModel ** [this->size];
	for (int i = 0; i < this->size; i++) {
		this->model_board[i] = new TileModel * [this->size];
		for (int j = 0; j < this->size; j++) {
			this->model_board[i][j] = new TileModel(this->grid[i][j]->currentValue, i, j);
		}
	}
	this->modelShader = new ShaderProgram("shaders/model_v_lambert.glsl", NULL, "shaders/model_f_lambert.glsl");
	this->Board::generate();
	this->Board::shuffleBoard();
	this->Board::printBoard();
}

Board3D::~Board3D() {
	for (int i = 0; i < this->size; i++) {
		for (int j = 0; j < this->size; j++)
			delete this->model_board[i][j];
		delete this->model_board[i];
	}
	delete this->model_board;
}

void Board3D::initModels() {
	for (int i = 0; i < this->size; i++) {
		for (int j = 0; j < this->size; j++) {
			this->model_board[i][j]->value = this->grid[i][j]->currentValue;
		}
	}
}

void Board3D::drawBoard(double tTime) {
	//rysyj ka¿dy model po kolei?
	//dunno ³ot to do here
}
