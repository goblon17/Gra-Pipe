#include "TileModel.h"

TileModel::TileModel(int val, int x, int y) {
	this->value = val;
	this->x = x;
	this->y = y;
	this->center = new Models::Sphere(tile_sphere_radius, tile_sphere_meridians, tile_sphere_parallels);
	this->pipe = new Cylinder(tile_pipe_up_base_radius, tile_pipe_down_base_radius, tile_pipe_height, tile_pipe_sectors, tile_pipe_stacks, tile_pipe_smooth);
}

TileModel::~TileModel() {
	delete this->pipe;
	delete this->center;
}

void TileModel::drawTile(int size, tile* til, ShaderProgram* modelShader, double dTime) {
	this->rotate(dTime);

	glm::mat4 M = glm::mat4(1.0f);
	M = glm::translate(M, glm::vec3((this->y - size * 0.5 + 0.5f) * 0.5f, 0.0f, (this->x - size * 0.5f + 0.5f) * 0.5f));
	M = glm::rotate(M, this->currentRotation, glm::vec3(0, 1, 0));
	glUniformMatrix4fv(modelShader->u("M"), 1, false, glm::value_ptr(M));

	glUniform1i(modelShader->u("highlight"), til->isHighlighted);

	if (til->isTarget) glUniform4f(modelShader->u("color"), 0, 1, 0, 1);
	else if (til->isSource) glUniform4f(modelShader->u("color"), 1, 0, 0, 1);
	else glUniform4f(modelShader->u("color"), 1, 1, 1, 1);
	this->center->drawSolid();

	glUniform4f(modelShader->u("color"), 1, 1, 1, 1);

	glm::mat4 M1 = M;
	if (this->value & 1) {
		M1 = glm::translate(M, glm::vec3(0.0f, 0.0f, -tile_pipe_center_shift));
		M1 = glm::rotate(M1, -PI / 2, glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(modelShader->u("M"), 1, false, glm::value_ptr(M1));
		this->pipe->draw();
	}
	if (this->value & 2) {
		M1 = glm::translate(M, glm::vec3(tile_pipe_center_shift, 0.0f, 0.0f));
		M1 = glm::rotate(M1, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		M1 = glm::rotate(M1, -PI / 2, glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(modelShader->u("M"), 1, false, glm::value_ptr(M1));
		this->pipe->draw();
	}
	if (this->value & 4) {
		M1 = glm::translate(M, glm::vec3(0.0f, 0.0f, tile_pipe_center_shift));
		M1 = glm::rotate(M1, -PI / 2, glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(modelShader->u("M"), 1, false, glm::value_ptr(M1));
		this->pipe->draw();
	}
	if (this->value & 8) {
		M1 = glm::translate(M, glm::vec3(-tile_pipe_center_shift, 0.0f, 0.0f));
		M1 = glm::rotate(M1, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		M1 = glm::rotate(M1, -PI / 2, glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(modelShader->u("M"), 1, false, glm::value_ptr(M1));
		this->pipe->draw();
	}
}

void TileModel::rotate(double dTime) {
	if (this->rotationDirection == 0) {
		return;
	}
	this->currentRotation += this->rotationDirection * (float)dTime * this->rotSpeed;
	bool t = glm::abs(this->desiredRotation - this->currentRotation) > PI;
	if (!t && ((this->rotationDirection == 1 && this->currentRotation >= this->desiredRotation) || (this->rotationDirection == -1 && this->currentRotation <= this->desiredRotation))) {
		this->currentRotation = this->desiredRotation;
		this->rotationDirection = 0;
	}
	if (this->currentRotation >= 2 * PI) {
		this->currentRotation -= 2 * PI;
	}
	if (this->currentRotation < 0) {
		this->currentRotation += 2 * PI;
	}
}

void TileModel::rotateLeft() {
	this->desiredRotation += PI / 2;
	if (this->desiredRotation >= 2 * PI) {
		this->desiredRotation -= 2 * PI;
	}
	this->rotationDirection = 1;
}

void TileModel::rotateRight() {
	this->desiredRotation -= PI / 2;
	if (this->desiredRotation < 0) {
		this->desiredRotation += 2 * PI;
	}
	this->rotationDirection = -1;
}