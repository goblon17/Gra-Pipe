#ifndef BOARD3D_H
#define BOARD3D_H

#include <glm/gtc/type_ptr.hpp>
#include "Board.h"
#include "TileModel.h"
#include "Sphere.h"
#include "Camera.h"


class Board3D : public Board {
	TileModel*** model_board;
	
public:
	ShaderProgram* modelShader;
	void initModels();
	void drawBoard(Camera *camera, double dTime);
	Board3D(int size);
	~Board3D();
};

#endif
