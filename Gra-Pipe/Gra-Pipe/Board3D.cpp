#include "Board3D.h"

Board3D::Board3D(int size) : Board(size) {
	this->modelShader = new ShaderProgram("shaders/model_v_lambert.glsl", NULL, "shaders/model_f_lambert.glsl");
	this->model_board = new PipeModel ** [this->size];
	for (int i = 0; i < this->size; i++) {
		this->model_board[i] = new PipeModel * [this->size];
		for (int j = 0; j < this->size; j++) {
			this->model_board[i][j] = new PipeModel(this->grid[i][j]->currentValue, i, j);
			//this->model_board[i][j]
		}
	}
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

		}
	}
}

void Board3D::drawBoard(glm::mat4 P, glm::mat4 V, double tTime) {
	this->modelShader->use();
	glUniformMatrix4fv(this->modelShader->u("P"), 1, false, glm::value_ptr(P));
	glUniformMatrix4fv(this->modelShader->u("P"), 1, false, glm::value_ptr(P));

	for (int i = 0; i < this->size; i++) {
		for (int j = 0; j < this->size; j++) {
			glm::mat4 modelMatrix = glm::mat4(1.0f);
			glUniformMatrix4fv(this->modelShader->u("M"), 1, false, glm::value_ptr(modelMatrix));
			glUniform4f(this->modelShader->u("color"), 1, 1, 0, 1);
			this->model_board[i][j]->center.drawSolid();
		}
	}

}
