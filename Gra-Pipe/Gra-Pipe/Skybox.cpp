#include "Skybox.h"

Skybox::Skybox() {
	this->skyboxShader = new ShaderProgram("shaders/skybox_v_shader.glsl", NULL, "shaders/skybox_f_shader.glsl");
	this->tex = readCubeMapTexture(this->filenames);
}

Skybox::~Skybox() {
	delete skyboxShader;
}

void Skybox::Draw(Camera* camera) {
	this->skyboxShader->use();

	glUniformMatrix4fv(skyboxShader->u("P"), 1, false, glm::value_ptr(camera->Pmat));
	glUniformMatrix4fv(skyboxShader->u("V"), 1, false, glm::value_ptr(camera->Vmat));
	glUniformMatrix4fv(skyboxShader->u("M"), 1, false, glm::value_ptr(this->M));

	glUniform1i(skyboxShader->u("skybox"), 0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, this->tex);

	glUniform1f(skyboxShader->u("Size"), this->size);

	glEnableVertexAttribArray(skyboxShader->a("Vertex"));
	glVertexAttribPointer(skyboxShader->a("Vertex"), 3, GL_FLOAT, false, 0, this->verts);

	glDrawArrays(GL_TRIANGLES, 0, vertCount);

	glDisableVertexAttribArray(skyboxShader->a("Vertex"));
}