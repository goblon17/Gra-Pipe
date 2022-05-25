#ifndef PAUSE_H
#define PAUSE_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>
#include "Utility.h"
#include "Camera.h"
#include "Button.h"
#include "Scene.h"
#include "Utility2.h"

class Pause : public Scene
{
private:

public:
	Pause(WindowSize* winSize, CursorState* cursor, Camera* camera);
	~Pause();
	void Draw(double dTime, ShaderProgram* guiShader);
	void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods, Game* game);
	void cursorPosCallback(GLFWwindow* window, double xPos, double yPos);
};

#endif