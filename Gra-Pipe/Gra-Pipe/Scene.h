#ifndef SCENE_H
#define SCENE_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>
#include "Skybox.h"
#include "GUItexture.h"
#include "Button.h"
#include "Utility.h"

class Game;

class Scene
{
protected:
	GUItexture* logo = nullptr;
	std::vector<Button*> buttons;
	WindowSize* winSize = nullptr;
	CursorState* cursor = nullptr;
	int getHighlightedID();
public:
	Scene() {};
	~Scene() {};
	virtual void Draw(double dTime, Camera* camera, ShaderProgram* guiShader) {};
	virtual void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods, Game* game) {};
	virtual void cursorPosCallback(GLFWwindow* window, double xPos, double yPos) {};
	virtual void scrollCallback(GLFWwindow* window, double xOffset, double yOffset) {};
	virtual void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {};
};

#endif