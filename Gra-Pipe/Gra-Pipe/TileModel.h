#ifndef PIPEMODEL_H
#define PIPEMODEL_H

#include "Sphere.h"
#include "shaderprogram.h"
#include "Cylinder.h"
#include <glm/glm.hpp>


class TileModel {
public:
	int value;
	int x, y;
	Models::Sphere *center;
	std::vector<Cylinder*> pipes;
	
	void initModel();
	void drawTile(glm::mat4 M);
	TileModel(int val, int x, int y);
	~TileModel();
};

#endif