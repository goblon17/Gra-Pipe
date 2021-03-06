#include "Board3D.h"

Board3D::Board3D(Camera* camera, WindowSize* winSize, int size) : Board(size) {
	this->camera = camera;
	this->winSize = winSize;
	this->modelShader = new ShaderProgram("shaders/model_v_lambert.glsl", NULL, "shaders/model_f_lambert.glsl");
	this->initNewBoard(size);
	this->metalTex = readTexture2D("textures/polished_diorite.png");
	this->specTex = readTexture2D("textures/spec.png");
	this->isWon = false;
}

Board3D::~Board3D() {
	for (int i = 0; i < this->size; i++) {
		for (int j = 0; j < this->size; j++)
			delete this->model_board[i][j];
		delete this->model_board[i];
	}
	delete this->model_board;
}

void Board3D::initNewBoard(int size) {
	if (this->grid != NULL) {
		for (int i = 0; i < this->size; i++) {
			for (int j = 0; j < this->size; j++)
				delete this->grid[i][j];
			delete this->grid[i];
		}
		delete this->grid;
	}

	if (this->model_board != NULL) {
		for (int i = 0; i < this->size; i++) {
			for (int j = 0; j < this->size; j++)
				delete this->model_board[i][j];
			delete this->model_board[i];
		}
		delete this->model_board;
	}

	this->size = size;

	this->grid = new tile * *[this->size];
	for (int i = 0; i < this->size; i++) {
		this->grid[i] = new tile * [this->size];
		for (int j = 0; j < this->size; j++) {
			this->grid[i][j] = new tile(i, j, 0, 0);
		}
	}

	this->generate();

	this->model_board = new TileModel * *[this->size];
	for (int i = 0; i < this->size; i++) {
		this->model_board[i] = new TileModel * [this->size];
		for (int j = 0; j < this->size; j++) {
			this->model_board[i][j] = new TileModel(this->grid[i][j]->correctValue, i, j);
		}
	}
	
	this->Board::shuffleBoard();
	this->initModels();
	this->printBoard();
	this->isWon = false;
}

void Board3D::initModels() {
	for (int i = 0; i < this->size; i++) {
		for (int j = 0; j < this->size; j++) {
			this->model_board[j][i]->value = this->grid[j][i]->currentValue;
		}
	}
}

void Board3D::drawBoard(double dTime) {

	this->modelShader->use();
	glUniformMatrix4fv(this->modelShader->u("P"), 1, false, glm::value_ptr(this->camera->Pmat));
	glUniformMatrix4fv(this->modelShader->u("V"), 1, false, glm::value_ptr(this->camera->Vmat));
	
	glUniform1i(this->modelShader->u("mainTexture"), 0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, this->metalTex);

	glUniform1i(this->modelShader->u("specTexture"), 1);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, this->specTex);
	
	glm::mat4 M = glm::mat4(1.0f);
	
	for (int i = 0; i < this->size; i++) {
		for (int j = 0; j < this->size; j++) {			
			this->model_board[j][i]->drawTile(this->size, this->grid[j][i], this->modelShader, dTime);
		}
	}
}

void Board3D::cursorPosCallback(GLFWwindow* window, double xPos, double yPos) {
	if (glfwGetInputMode(window, GLFW_CURSOR) != GLFW_CURSOR_NORMAL) {
		return;
	}
	glm::vec3 mousePos = caclMouseToWorld(this->camera, this->winSize, xPos, yPos, 0);
	calcWorldToGrid(mousePos);

	this->flushSelection();

	if (this->inbounds()) {
		this->grid[this->gridPos.y][this->gridPos.x]->isHighlighted = true;
	}
}

void Board3D::leftMouseButton() {
	if (this->inbounds()) {
		int x = this->gridPos.x;
		int y = this->gridPos.y;
		this->rotate(1, this->grid[y][x]);

		this->model_board[y][x]->rotateLeft();

		if (this->checkWin()) {
			this->isWon = true;
			printf("WYGRANA1!!!11oneoneone\n");
		}
		else {
			this->isWon = false;
		}
	}
}

void Board3D::rightMouseButton() {
	if (this->inbounds()) {
		int x = this->gridPos.x;
		int y = this->gridPos.y;
		this->rotate(3, this->grid[y][x]);

		this->model_board[y][x]->rotateRight();

		if (this->checkWin()) {
			this->isWon = true;
			printf("WYGRANA1!!!11oneoneone\n");
		}
		else {
			this->isWon = false;
		}
	}
}

void Board3D::calcWorldToGrid(glm::vec3 mousePos) {
	this->gridPos.x = (int)round(0.5 * this->size - 0.5 + 2 * mousePos[0]);
	this->gridPos.y = (int)round(0.5 * this->size - 0.5 + 2 * mousePos[2]);
}

bool Board3D::inbounds() {
	return this->gridPos.x >= 0 && this->gridPos.y >= 0 && this->gridPos.x < this->size&& this->gridPos.y < this->size;
}

void Board3D::flushSelection() {
	for (int i = 0; i < this->size; i++) {
		for (int j = 0; j < this->size; j++) {
			this->grid[i][j]->isHighlighted = false;
		}
	}
}