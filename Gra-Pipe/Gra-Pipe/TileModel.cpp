#include "TileModel.h"
#include "glm/ext/matrix_transform.hpp"
#include "Utility.h"

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

void TileModel::drawTile(glm::mat4 M) {
	glm::mat4 M1 = M;
	this->center->drawSolid();

	for (auto i : this->pipes) {
		if (this->value & 1) {
			M1 = glm::translate(M, glm::vec3(0.5f, 0.0f, 0.0f));
			printf("xd");
			i->draw();
		}	
	}
}