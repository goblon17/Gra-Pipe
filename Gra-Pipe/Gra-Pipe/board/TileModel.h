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
private:
	int x, y;
	Models::Sphere *center;
	Cylinder* pipe;

	float rotSpeed = PI * 3;
	float desiredRotation = 0;
	float currentRotation = 0;
	int rotationDirection = 0;

	void rotate(double dTime);

public:
	int value;
	void drawTile(int size, tile* til, ShaderProgram* modelShader, double dTime);
	TileModel(int val, int x, int y);
	~TileModel();
	void rotateLeft();
	void rotateRight();
};

#endif