#ifndef SETTINGS_H
#define SETTINGS_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>
#include "GUItexture.h"
#include "Utility.h"
#include "Camera.h"
#include "Button.h"
#include "MultipleStateButton.h"
#include "Scene.h"
#include "Utility2.h"

class Settings : public Scene
{
private:

public:
	int sensitivity = 0;
	Settings(WindowSize* winSize, CursorState* cursor, Camera* camera);
	~Settings();
	void Draw(double dTime, ShaderProgram* guiShader);
	void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods, Game* game);
	void cursorPosCallback(GLFWwindow* window, double xPos, double yPos);
};

#endif