#ifndef BUTTON_H
#define BUTTON_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include "GUItexture.h"
#include "shaderprogram.h"

class Button
{
private:
	GUItexture* normal = nullptr;
	GUItexture* highlighted = nullptr;
	glm::vec2 pos = glm::vec2(0, 0);
	glm::vec2 size = glm::vec2(0, 0);
	bool inBounds(double normalX, double normalY, float ar);
public:
	int state = 0;
	bool isSeleced = false;
	Button(const char* normal_texture, const char* highlighted_texture, glm::vec2 pos, glm::vec2 size);
	Button() {};
	~Button();
	virtual void Draw(Camera* camera, ShaderProgram* shader);
	virtual void mousePosCallback(GLFWwindow* window, double X, double Y, WindowSize* winSize);
	virtual void nextState() {};
};

#endif