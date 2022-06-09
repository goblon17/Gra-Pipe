#ifndef MULTIPLESTATEBUTTON_H
#define MULTIPLESTATEBUTTON_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <cstdarg>
#include <vector>
#include "GUItexture.h"
#include "utility/shaderprogram.h"
#include "Button.h"

class MultipleStateButton : public Button
{
private:
	std::vector<Button*> buttons;
public:
	MultipleStateButton(int n, ...);
	~MultipleStateButton();
	void Draw(Camera* camera, ShaderProgram* shader);
	void mousePosCallback(GLFWwindow* window, double X, double Y, WindowSize* winSize);
	void nextState();
};

#endif