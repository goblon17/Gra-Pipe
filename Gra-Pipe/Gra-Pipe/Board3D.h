#ifndef BOARD3D_H
#define BOARD3D_H

#include <glm/gtc/type_ptr.hpp>
#include "Board.h"
#include "TileModel.h"


class Board3D : public Board {
	TileModel*** model_board;
	ShaderProgram* modelShader;
	
public:
	void initModels();
	void drawBoard(double tTime);
	Board3D(int size);
	~Board3D();
};

#endif
