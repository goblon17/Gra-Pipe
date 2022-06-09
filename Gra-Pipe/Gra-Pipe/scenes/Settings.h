#ifndef SETTINGS_H
#define SETTINGS_H

#include <windows.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>
#include "gui/GUItexture.h"
#include "utility/Utility.h"
#include "utility/Camera.h"
#include "gui/Button.h"
#include "gui/MultipleStateButton.h"
#include "Scene.h"
#include "utility/Utility2.h"

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