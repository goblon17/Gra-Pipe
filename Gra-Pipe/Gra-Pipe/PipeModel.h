#ifndef PIPEMODEL_H
#define PIPEMODEL_H

#include "Sphere.h"


class PipeModel {
	int value;
	int x, y;
	
public:
	Models::Sphere center;

	void Rotate(int n);
	PipeModel(int val, int x, int y);
	//~PipeModel();
};

#endif