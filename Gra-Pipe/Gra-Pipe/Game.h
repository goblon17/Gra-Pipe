#ifndef GAME_H
#define GAME_H

#include <vector>
#include "shaderprogram.h"
#include "Utility.h"
#include "Camera.h"
#include "Scene.h"
#include "scenes/Menu.h"
#include "scenes/Play.h"
#include "scenes/Pause.h"
#include "scenes/Settings.h"

class Game
{
private:
	ShaderProgram* guiShader;
	Skybox* skybox;
	Camera* camera;
	int currentState = GAME_SCENE_MENU;
	std::vector<Scene*> scenes;
	WindowSize* winSize = nullptr;
	CursorState* cursor = nullptr;
public:
	Game(WindowSize* winSize, CursorState* cursor, Camera* camera);
	~Game();
	void setCurrentState(int state);
	void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
	void cursorPosCallback(GLFWwindow* window, double xPos, double yPos);
	void scrollCallback(GLFWwindow* window, double xOffset, double yOffset);
	void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
	void Draw(double dTime);
};

#endif