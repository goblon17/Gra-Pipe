#ifndef GUITEXTURE_H
#define GUITEXTURE_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "shaderprogram.h"
#include "Camera.h"
#include "Utility.h"

class GUItexture
{
private:
	GLuint tex;
	glm::vec2 pos;
	glm::vec2 size;
	float verts[8] = { -1, 1, -1, -1, 1, 1, 1, -1 };
	int vertexCount = 4;
	glm::mat4 M;
public:
	GUItexture(const char* src, glm::vec2 pos, glm::vec2 size);
	void Draw(Camera* camera, ShaderProgram* shader);
};

#endif