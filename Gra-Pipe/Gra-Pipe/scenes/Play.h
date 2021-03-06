#ifndef PLAY_H
#define PLAY_H

#include <windows.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>
#include "utility/Utility.h"
#include "utility/Camera.h"
#include "gui/Button.h"
#include "Scene.h"
#include "board/Board3D.h"
#include "utility/Utility2.h"

class Board3D;

class Play : public Scene
{
private:
	Board3D* board;
public:
	Play(WindowSize* winSize, CursorState* cursor, Camera* camera, Board3D* board);
	~Play();
	void Draw(double dTime, ShaderProgram* guiShader);
	void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods, Game* game);
	void cursorPosCallback(GLFWwindow* window, double xPos, double yPos);
	void scrollCallback(GLFWwindow* window, double xOffset, double yOffset);
};

#endif