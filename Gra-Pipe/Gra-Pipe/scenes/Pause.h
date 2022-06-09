#ifndef PAUSE_H
#define PAUSE_H

#include <windows.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>
#include "utility/Utility.h"
#include "utility/Camera.h"
#include "gui/Button.h"
#include "Scene.h"
#include "utility/Utility2.h"

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