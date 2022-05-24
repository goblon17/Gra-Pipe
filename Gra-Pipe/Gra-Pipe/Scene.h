#ifndef SCENE_H
#define SCENE_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>
#include "GUItexture.h"
#include "Button.h"
#include "Utility.h"

class Scene
{
protected:
	GUItexture* logo;
	std::vector<Button*> buttons;
	WindowSize* winSize;
	CursorState* cursor;
	int getHighlightedID();
public:
	Scene() {};
	~Scene() {};
	void Draw(Camera* camera, ShaderProgram* shader);
	virtual void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {};
	virtual void cursorPosCallback(GLFWwindow* window, double xPos, double yPos) {};
	virtual void scrollCallback(GLFWwindow* window, double xOffset, double yOffset) {};
	virtual void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {};
};

#endif