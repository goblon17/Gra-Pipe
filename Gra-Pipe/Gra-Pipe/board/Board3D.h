#ifndef BOARD3D_H
#define BOARD3D_H

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Board.h"
#include "TileModel.h"
#include "models/Sphere.h"
#include "utility/Camera.h"
#include "utility/Utility.h"
#include "utility/Utility2.h"

class Board3D : public Board {
	TileModel*** model_board;
	Camera* camera;
	WindowSize* winSize;
	glm::ivec2 gridPos;
	GLuint metalTex;
	GLuint specTex;
public:
	bool isWon;
	ShaderProgram* modelShader;
	void initNewBoard(int size);
	void initModels();
	void calcWorldToGrid(glm::vec3 mousePos);
	void drawBoard(double dTime);
	void cursorPosCallback(GLFWwindow* window, double xPos, double yPos);
	void leftMouseButton();
	void rightMouseButton();
	bool inbounds();
	void flushSelection();
	Board3D(Camera* camera, WindowSize* winSize, int size);
	~Board3D();
};

#endif
