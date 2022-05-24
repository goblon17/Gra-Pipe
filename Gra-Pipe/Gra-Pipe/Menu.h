#ifndef MENU_H
#define MENU_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>
#include "GUItexture.h"
#include "Utility.h"
#include "Camera.h"
#include "Button.h"
#include "Scene.h"

class Menu : public Scene
{
private:

public:
	Menu(WindowSize* winSize, CursorState* cursor);
	~Menu();
	void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
	void cursorPosCallback(GLFWwindow* window, double xPos, double yPos);
	void scrollCallback(GLFWwindow* window, double xOffset, double yOffset);
};

#endif