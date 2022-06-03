#include "Board3D.h"

Board3D::Board3D(Camera* camera, WindowSize* winSize, int size) : Board(size) {
	this->camera = camera;
	this->winSize = winSize;
	this->modelShader = new ShaderProgram("shaders/model_v_lambert.glsl", NULL, "shaders/model_f_lambert.glsl");
	this->initNewBoard(size);
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
}

void Board3D::initModels() {
	for (int i = 0; i < this->size; i++) {
		for (int j = 0; j < this->size; j++) {
			this->model_board[j][i]->value = this->grid[i][j]->currentValue;
			this->model_board[j][i]->initModel();
		}
	}
}

void Board3D::drawBoard(double dTime) {
	//narazie u�y�em lamberta

	this->modelShader->use();
	glUniformMatrix4fv(this->modelShader->u("P"), 1, false, glm::value_ptr(this->camera->Pmat));
	glUniformMatrix4fv(this->modelShader->u("V"), 1, false, glm::value_ptr(this->camera->Vmat));
	
	glm::mat4 M = glm::mat4(1.0f);
	
	for (int i = 0; i < this->size; i++) {
		for (int j = 0; j < this->size; j++) {
			M = glm::mat4(1.0f);
			M = glm::translate(M, glm::vec3((j - this->size * 0.5 + 0.5f) * 0.5f, 0.0f, (i - this->size * 0.5f + 0.5f) * 0.5f));
			glUniformMatrix4fv(this->modelShader->u("M"), 1, false, glm::value_ptr(M));

			if (this->grid[i][j]->isTarget) glUniform4f(this->modelShader->u("color"), 0, 1, 0, 1);
			else if (this->grid[i][j]->isSource) glUniform4f(this->modelShader->u("color"), 1, 0, 0, 1);
			else glUniform4f(this->modelShader->u("color"), 1, 1, 0, 1);
			this->model_board[j][i]->center->drawSolid();
			
			glm::mat4 M1 = M;
			for (auto k : this->model_board[j][i]->pipes) {
				if (this->model_board[j][i]->value & 1) {
					M1 = glm::translate(M, glm::vec3(0.0f, 0.0f, -tile_pipe_center_shift));
					glUniformMatrix4fv(this->modelShader->u("M"), 1, false, glm::value_ptr(M1));
					k->draw();
				}
				if (this->model_board[j][i]->value & 2) {
					M1 = glm::translate(M, glm::vec3(tile_pipe_center_shift, 0.0f, 0.0f));
					M1 = glm::rotate(M1, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
					glUniformMatrix4fv(this->modelShader->u("M"), 1, false, glm::value_ptr(M1));
					k->draw();
				}
				if (this->model_board[j][i]->value & 4) {
					M1 = glm::translate(M, glm::vec3(0.0f, 0.0f, tile_pipe_center_shift));
					glUniformMatrix4fv(this->modelShader->u("M"), 1, false, glm::value_ptr(M1));
					k->draw();
				}
				if (this->model_board[j][i]->value & 8) {
					M1 = glm::translate(M, glm::vec3(-tile_pipe_center_shift, 0.0f, 0.0f));
					M1 = glm::rotate(M1, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
					glUniformMatrix4fv(this->modelShader->u("M"), 1, false, glm::value_ptr(M1));
					k->draw();
				}
			}
		}
	}
}

void Board3D::cursorPosCallback(GLFWwindow* window, double xPos, double yPos) {
	glm::vec3 mousePos = caclMouseToWorld(this->camera, this->winSize, xPos, yPos, 0); // Tu masz pozycje w swiecie

	glm::vec2 gridPos = calcWorldToGrid(mousePos);

	printf("%f %f %f   %d %d\n", mousePos[0], mousePos[1], mousePos[2], gridPos[0], gridPos[1]);
}

void Board3D::leftMouseButton() {
	// rotate 3
}

void Board3D::rightMouseButton() {
	//rotate 1
}

glm::vec2 Board3D::calcWorldToGrid(glm::vec3 mousePos) {
	int x_grid = 2 * (mousePos[0] + model_size * 0.5f) + 0.25 * (this->size - 1) + 1;
	int y_grid = 2 * (mousePos[2] + model_size * 0.5f) + 0.25 * (this->size - 1) + 1;
	printf("%d %d\n", x_grid, y_grid);
	return glm::vec2(x_grid, y_grid);
}