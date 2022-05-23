#include "Skybox.h"

Skybox::Skybox() {
	this->skyboxShader = new ShaderProgram("shaders/skybox_v_shader.glsl", NULL, "shaders/skybox_f_shader.glsl");
}

Skybox::~Skybox() {
	delete skyboxShader;
}