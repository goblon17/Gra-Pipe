#include "GUItexture.h"

GUItexture::GUItexture(const char* src, glm::vec2 pos, glm::vec2 size) {
	this->tex = readTexture2D(src);
	this->pos = pos;
	this->size = size;
	this->M = glm::mat4(1);
}

void GUItexture::Draw(Camera* camera, ShaderProgram* shader) {
	shader->use();

	this->M = glm::mat4(1);
	float x = this->pos.x + glm::sign(this->pos.x) * (this->size.x - this->size.x / camera->aspectRatio);
	this->M = glm::translate(M, glm::vec3(x, this->pos.y, 0));
	this->M = glm::scale(M, glm::vec3(this->size, 0));

	glUniformMatrix4fv(shader->u("M"), 1, false, glm::value_ptr(this->M));
	glUniform1f(shader->u("aspectRatio"), camera->aspectRatio);

	glUniform1i(shader->u("tex"), 0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, this->tex);

	glEnableVertexAttribArray(shader->a("Vertex"));
	glVertexAttribPointer(shader->a("Vertex"), 2, GL_FLOAT, false, 0, this->verts);

	glDrawArrays(GL_TRIANGLE_STRIP, 0, this->vertexCount);

	glDisableVertexAttribArray(shader->a("Vertex"));
}