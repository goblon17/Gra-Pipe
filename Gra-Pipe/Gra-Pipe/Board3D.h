#ifndef BOARD3D_H
#define BOARD3D_H

#include <glm/gtc/type_ptr.hpp>
#include "Board.h"
#include "PipeModel.h"
#include "shaderprogram.h"


class Board3D : public Board {
	Board board;
	PipeModel*** model_board;
	ShaderProgram *modelShader;
	
public:
	void initModels();
	void drawBoard(glm::mat4 P, glm::mat4 V, double tTime);
	Board3D(int size);
	~Board3D();
};

#endif
