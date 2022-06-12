#ifndef PIPEMODEL_H
#define PIPEMODEL_H

#include "models/Sphere.h"
#include "utility/shaderprogram.h"
#include "models/Cylinder.h"
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "glm/ext/matrix_transform.hpp"
#include "utility/Utility.h"


class TileModel {
public:
	int value;
	int x, y;
	Models::Sphere *center;
	std::vector<Cylinder*> pipes;
	
	void initModel();
	void drawTile(int size, tile* til, ShaderProgram* modelShader);
	TileModel(int val, int x, int y);
	~TileModel();
};

#endif