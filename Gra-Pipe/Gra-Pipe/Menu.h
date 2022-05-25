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
#include "Utility2.h"

class Menu : public Scene
{
private:
	const double rotationSpeed = PI;
public:
	Menu(WindowSize* winSize, CursorState* cursor);
	~Menu();
	void Draw(double dTime, Camera* camera, ShaderProgram* guiShader);
	void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods, Game* game);
	void cursorPosCallback(GLFWwindow* window, double xPos, double yPos);
};

#endif