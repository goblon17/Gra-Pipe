#ifndef WIN_H
#define WIN_H

#include <windows.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>
#include "GUItexture.h"
#include "Utility.h"
#include "Camera.h"
#include "Button.h"
#include "Scene.h"
#include "Utility2.h"

class Win : public Scene
{
private:
	int* boardSize;
public:
	Win(WindowSize* winSize, CursorState* cursor, Camera* camera, int* boardSize);
	~Win();
	void Draw(double dTime, ShaderProgram* guiShader);
	void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods, Game* game);
	void cursorPosCallback(GLFWwindow* window, double xPos, double yPos);
};

#endif