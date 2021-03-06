#ifndef SCENE_H
#define SCENE_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>
#include "utility/Camera.h"
#include "gui/GUItexture.h"
#include "gui/Button.h"
#include "utility/Utility.h"

class Game;

class Scene
{
protected:
	GUItexture* logo = nullptr;
	WindowSize* winSize = nullptr;
	CursorState* cursor = nullptr;
	Camera* camera = nullptr;
	int getHighlightedID();
public:
	std::vector<Button*> buttons;
	Scene() {};
	~Scene() {};
	virtual void Draw(double dTime, ShaderProgram* guiShader) {};
	virtual void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods, Game* game) {};
	virtual void cursorPosCallback(GLFWwindow* window, double xPos, double yPos) {};
	virtual void scrollCallback(GLFWwindow* window, double xOffset, double yOffset) {};
	virtual void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {};
};

#endif