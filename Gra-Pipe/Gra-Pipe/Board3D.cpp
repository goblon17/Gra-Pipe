#include "Board3D.h"

Board3D::Board3D(Camera* camera, WindowSize* winSize, int size) : Board(size) {
	this->camera = camera;
	this->winSize = winSize;
	
	this->model_board = new TileModel ** [this->size];
	for (int i = 0; i < this->size; i++) {
		this->model_board[i] = new TileModel * [this->size];
		for (int j = 0; j < this->size; j++) {
			this->model_board[i][j] = new TileModel(this->grid[i][j]->currentValue, i, j);
		}
	}
	this->modelShader = new ShaderProgram("shaders/model_v_lambert.glsl", NULL, "shaders/model_f_lambert.glsl");
	this->generate();
	//this->Board::shuffleBoard();
	this->printBoard();
	this->initModels();
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
			this->model_board[i][j]->initModel();
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

			if (this->grid[j][i]->isTarget) glUniform4f(this->modelShader->u("color"), 0, 1, 0, 1);
			else if (this->grid[j][i]->isSource) glUniform4f(this->modelShader->u("color"), 1, 0, 0, 1);
			else glUniform4f(this->modelShader->u("color"), 1, 1, 0, 1);
			this->model_board[j][i]->center->drawSolid();
			
			glm::mat4 M1 = M;
			for (auto k : this->model_board[j][i]->pipes) {
				if (this->model_board[j][i]->value & 1) {
					M1 = glm::translate(M, glm::vec3(0.0f, 0.0f, -0.15f));
					glUniformMatrix4fv(this->modelShader->u("M"), 1, false, glm::value_ptr(M1));
					k->draw();
				}
				if (this->model_board[j][i]->value & 2) {
					M1 = glm::translate(M, glm::vec3(0.15f, 0.0f, 0.0f));
					M1 = glm::rotate(M1, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
					glUniformMatrix4fv(this->modelShader->u("M"), 1, false, glm::value_ptr(M1));
					k->draw();
				}
				if (this->model_board[j][i]->value & 4) {
					M1 = glm::translate(M, glm::vec3(0.0f, 0.0f, 0.15f));
					glUniformMatrix4fv(this->modelShader->u("M"), 1, false, glm::value_ptr(M1));
					k->draw();
				}
				if (this->model_board[j][i]->value & 8) {
					M1 = glm::translate(M, glm::vec3(-0.15f, 0.0f, 0.0f));
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
}

void Board3D::leftMouseButton() {

}

void Board3D::rightMouseButton() {

}