#ifndef PLAY_H
#define PLAY_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>
#include "Utility.h"
#include "Camera.h"
#include "Button.h"
#include "Scene.h"
#include "Utility2.h"


class Play : public Scene
{
private:

public:
	Play(WindowSize* winSize, CursorState* cursor, Camera* camera);
	~Play();
	void Draw(double dTime, ShaderProgram* guiShader);
	void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods, Game* game);
	void cursorPosCallback(GLFWwindow* window, double xPos, double yPos);
	void scrollCallback(GLFWwindow* window, double xOffset, double yOffset);
};

#endif