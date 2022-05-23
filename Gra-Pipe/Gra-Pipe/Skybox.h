#ifndef SKYBOX_H
#define SKYBOX_H

#include <glm/glm.hpp>
#include "shaderprogram.h"

class Skybox
{
public:
	float verts[144] = {
		//Sciana 1
		1.0f,-1.0f,-1.0f,1.0f,
	   -1.0f, 1.0f,-1.0f,1.0f,
	   -1.0f,-1.0f,-1.0f,1.0f,

		1.0f,-1.0f,-1.0f,1.0f,
		1.0f, 1.0f,-1.0f,1.0f,
	   -1.0f, 1.0f,-1.0f,1.0f,

	   //Sciana 2
	   -1.0f,-1.0f, 1.0f,1.0f,
		1.0f, 1.0f, 1.0f,1.0f,
		1.0f,-1.0f, 1.0f,1.0f,

	   -1.0f,-1.0f, 1.0f,1.0f,
	   -1.0f, 1.0f, 1.0f,1.0f,
		1.0f, 1.0f, 1.0f,1.0f,


		//Sciana 3
		-1.0f,-1.0f,-1.0f,1.0f,
		 1.0f,-1.0f, 1.0f,1.0f,
		 1.0f,-1.0f,-1.0f,1.0f,

		-1.0f,-1.0f,-1.0f,1.0f,
		-1.0f,-1.0f, 1.0f,1.0f,
		 1.0f,-1.0f, 1.0f,1.0f,

		 //Sciana 4
		 -1.0f, 1.0f, 1.0f,1.0f,
		  1.0f, 1.0f,-1.0f,1.0f,
		  1.0f, 1.0f, 1.0f,1.0f,

		 -1.0f, 1.0f, 1.0f,1.0f,
		 -1.0f, 1.0f,-1.0f,1.0f,
		  1.0f, 1.0f,-1.0f,1.0f,

		  //Sciana 5
		  -1.0f,-1.0f,-1.0f,1.0f,
		  -1.0f, 1.0f, 1.0f,1.0f,
		  -1.0f,-1.0f, 1.0f,1.0f,

		  -1.0f,-1.0f,-1.0f,1.0f,
		  -1.0f, 1.0f,-1.0f,1.0f,
		  -1.0f, 1.0f, 1.0f,1.0f,

		  //Sciana 6
		   1.0f,-1.0f, 1.0f,1.0f,
		   1.0f, 1.0f,-1.0f,1.0f,
		   1.0f,-1.0f,-1.0f,1.0f,

		   1.0f,-1.0f, 1.0f,1.0f,
		   1.0f, 1.0f, 1.0f,1.0f,
		   1.0f, 1.0f,-1.0f,1.0f,
	};
	glm::mat4 M = glm::mat4(1);
	ShaderProgram* skyboxShader;
	Skybox();
	~Skybox();
};

#endif