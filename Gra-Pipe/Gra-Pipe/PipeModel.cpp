#include "PipeModel.h"

PipeModel::PipeModel(int val, int x, int y) {
	this->value = val;
	this->x = x;
	this->y = y;
	this->center = Models::Sphere(0.5, 36, 36);
}