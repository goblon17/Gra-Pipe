#ifndef SKYBOX_H
#define SKYBOX_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "shaderprogram.h"
#include <vector>
#include "Utility.h"
#include "Camera.h"

class Skybox
{
private:
	float verts[108] = {
		//Sciana 1
		1.0f,-1.0f,-1.0f,
	   -1.0f, 1.0f,-1.0f,
	   -1.0f,-1.0f,-1.0f,

		1.0f,-1.0f,-1.0f,
		1.0f, 1.0f,-1.0f,
	   -1.0f, 1.0f,-1.0f,

	   //Sciana 2
	   -1.0f,-1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f,-1.0f, 1.0f,

	   -1.0f,-1.0f, 1.0f,
	   -1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,


		//Sciana 3
		-1.0f,-1.0f,-1.0f,
		 1.0f,-1.0f, 1.0f,
		 1.0f,-1.0f,-1.0f,

		-1.0f,-1.0f,-1.0f,
		-1.0f,-1.0f, 1.0f,
		 1.0f,-1.0f, 1.0f,

		 //Sciana 4
		 -1.0f, 1.0f, 1.0f,
		  1.0f, 1.0f,-1.0f,
		  1.0f, 1.0f, 1.0f,

		 -1.0f, 1.0f, 1.0f,
		 -1.0f, 1.0f,-1.0f,
		  1.0f, 1.0f,-1.0f,

		  //Sciana 5
		  -1.0f,-1.0f,-1.0f,
		  -1.0f, 1.0f, 1.0f,
		  -1.0f,-1.0f, 1.0f,

		  -1.0f,-1.0f,-1.0f,
		  -1.0f, 1.0f,-1.0f,
		  -1.0f, 1.0f, 1.0f,

		  //Sciana 6
		   1.0f,-1.0f, 1.0f,
		   1.0f, 1.0f,-1.0f,
		   1.0f,-1.0f,-1.0f,

		   1.0f,-1.0f, 1.0f,
		   1.0f, 1.0f, 1.0f,
		   1.0f, 1.0f,-1.0f
	};
	int vertCount = 36;
	float size = 50;
	std::vector<const char*> filenames = { "textures/skybox/right.png", "textures/skybox/left.png", "textures/skybox/up.png", "textures/skybox/down.png", "textures/skybox/back.png", "textures/skybox/front.png"};
	glm::mat4 M = glm::mat4(1);
	GLuint tex;
	ShaderProgram* skyboxShader;

public:
	Skybox();
	~Skybox();

	void Draw(Camera* camera);
};

#endif