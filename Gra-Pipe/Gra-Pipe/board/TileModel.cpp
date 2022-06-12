#include "TileModel.h"

TileModel::TileModel(int val, int x, int y) {
	this->value = val;
	this->x = x;
	this->y = y;
	this->center = new Models::Sphere(tile_sphere_radius, tile_sphere_meridians, tile_sphere_parallels);
}

TileModel::~TileModel() {
	for (auto i : this->pipes)
		delete i;
	this->pipes.clear();
	delete this->center;
}

void TileModel::initModel() {
	for (int i = 1; i <= 8; i *= 2)
		if (this->value & i) {
			pipes.push_back(new Cylinder(tile_pipe_up_base_radius, tile_pipe_down_base_radius, tile_pipe_height,
							tile_pipe_sectors, tile_pipe_stacks, tile_pipe_smooth));
		}
}

void TileModel::drawTile(int size, tile* til, ShaderProgram* modelShader) {
	glm::mat4 M = glm::mat4(1.0f);
	M = glm::translate(M, glm::vec3((this->y - size * 0.5 + 0.5f) * 0.5f, 0.0f, (this->x - size * 0.5f + 0.5f) * 0.5f));
	glUniformMatrix4fv(modelShader->u("M"), 1, false, glm::value_ptr(M));

	glUniform1i(modelShader->u("highlight"), til->isHighlighted);

	if (til->isTarget) glUniform4f(modelShader->u("color"), 0, 1, 0, 1);
	else if (til->isSource) glUniform4f(modelShader->u("color"), 1, 0, 0, 1);
	else glUniform4f(modelShader->u("color"), 1, 1, 1, 1);
	this->center->drawSolid();

	glUniform4f(modelShader->u("color"), 1, 1, 1, 1);

	glm::mat4 M1 = M;
	for (auto k : this->pipes) {
		if (this->value & 1) {
			M1 = glm::translate(M, glm::vec3(0.0f, 0.0f, -tile_pipe_center_shift));
			M1 = glm::rotate(M1, -PI / 2, glm::vec3(0.0f, 0.0f, 1.0f));
			glUniformMatrix4fv(modelShader->u("M"), 1, false, glm::value_ptr(M1));
			k->draw();
		}
		if (this->value & 2) {
			M1 = glm::translate(M, glm::vec3(tile_pipe_center_shift, 0.0f, 0.0f));
			M1 = glm::rotate(M1, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
			M1 = glm::rotate(M1, -PI / 2, glm::vec3(0.0f, 0.0f, 1.0f));
			glUniformMatrix4fv(modelShader->u("M"), 1, false, glm::value_ptr(M1));
			k->draw();
		}
		if (this->value & 4) {
			M1 = glm::translate(M, glm::vec3(0.0f, 0.0f, tile_pipe_center_shift));
			M1 = glm::rotate(M1, -PI / 2, glm::vec3(0.0f, 0.0f, 1.0f));
			glUniformMatrix4fv(modelShader->u("M"), 1, false, glm::value_ptr(M1));
			k->draw();
		}
		if (this->value & 8) {
			M1 = glm::translate(M, glm::vec3(-tile_pipe_center_shift, 0.0f, 0.0f));
			M1 = glm::rotate(M1, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
			M1 = glm::rotate(M1, -PI / 2, glm::vec3(0.0f, 0.0f, 1.0f));
			glUniformMatrix4fv(modelShader->u("M"), 1, false, glm::value_ptr(M1));
			k->draw();
		}
	}
}