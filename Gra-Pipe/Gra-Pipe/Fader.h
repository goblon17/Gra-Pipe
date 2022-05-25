#ifndef FADER_H
#define FADER_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include "shaderprogram.h"

class Fader
{
private:
	float verts[8]{
		-1, -1,
		-1, 1,
		1, 1,
		1, -1
	};
	double fadeTime = 0.000002;
	float alfa = 0;
	ShaderProgram* fadeShader;
public:
	int fadeState = 0;
	Fader();
	~Fader();
	void Draw(double dTime);
	void FadeToBlack();
	void FadeFromBlack();
};

#endif