#ifndef GAME_H
#define GAME_H

#include <windows.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include "shaderprogram.h"
#include "Utility.h"
#include "Camera.h"
#include "Scene.h"
#include "Board3D.h"
#include "scenes/Menu.h"
#include "scenes/Play.h"
#include "scenes/Pause.h"
#include "scenes/Settings.h"

class Board3D;

class Game
{
private:
	ShaderProgram* guiShader;
	Skybox* skybox;
	int currentState = GAME_SCENE_MENU;
	std::vector<Scene*> scenes;
	WindowSize* winSize;
	CursorState* cursor;
public:
	int board_size;
	Board3D* board;
	Camera* camera;
	Game(WindowSize* winSize);
	~Game();
	void setCurrentState(int state);
	void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
	void cursorPosCallback(GLFWwindow* window, double xPos, double yPos);
	void scrollCallback(GLFWwindow* window, double xOffset, double yOffset);
	void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
	void windowResizeCallback(GLFWwindow* window, int width, int height);
	void Draw(double dTime);
};

#endif