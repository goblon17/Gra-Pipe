#ifndef BUTTON_H
#define BUTTON_H

#include <glm/glm.hpp>
#include "GUItexture.h"
#include "shaderprogram.h"

class Button
{
private:
	GUItexture* normal;
	GUItexture* highlighted;
	glm::vec2 pos;
	glm::vec2 size;
	bool inBounds(double normalX, double normalY);
public:
	bool isSeleced;
	Button(const char* normal_texture, const char* highlighted_texture, glm::vec2 pos, glm::vec2 size);
	~Button();
	void Draw(Camera* camera, ShaderProgram* shader);
	void mousePosCallback(double X, double Y, WindowSize* winSize);
};

#endif