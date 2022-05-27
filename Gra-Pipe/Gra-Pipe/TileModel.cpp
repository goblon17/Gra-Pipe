#include "TileModel.h"

TileModel::TileModel(int val, int x, int y) {
	this->value = val;
	this->x = x;
	this->y = y;
	this->center = Models::Sphere(0.5, 36, 36);
}

void TileModel::drawTile() {
	if (this->value & 1) {
		//draw pipe to north
	}
	if (this->value & 2) {
		//draw pipe to east
	}
	if (this->value & 4) {
		//draw pipe to south
	}
	if (this->value & 8) {
		//draw pipe to west
	}
}