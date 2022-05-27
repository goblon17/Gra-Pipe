#ifndef PIPEMODEL_H
#define PIPEMODEL_H

#include "Sphere.h"
#include "shaderprogram.h"


class TileModel {
public:
	int value;
	int x, y;
	Models::Sphere center;
	std::vector<int> pipes;

	void drawTile();
	TileModel(int val, int x, int y);
	//~TileModel();
};

#endif