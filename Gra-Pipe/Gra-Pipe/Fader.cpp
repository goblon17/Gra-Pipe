#include "Fader.h"

Fader::Fader() {
	this->fadeShader = new ShaderProgram("shaders/fade_v_shader.glsl", NULL, "shaders/fade_f_shader.glsl");
}

Fader::~Fader() {
	delete this->fadeShader;
}

void Fader::Draw(double dTime) {
	this->fadeShader->use();

	glUniform1f(this->fadeShader->u("alfa"), this->alfa);

	glEnableVertexAttribArray(this->fadeShader->a("Vertex"));
	glVertexAttribPointer(this->fadeShader->a("Vertex"), 2, GL_FLOAT, false, 0, this->verts);

	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	glDisableVertexAttribArray(this->fadeShader->a("Vertex"));

	if (this->alfa >= 0 && this->alfa <= 1) {
		this->alfa += dTime * this->fadeState * this->fadeTime;
	}
	else {
		this->alfa = (this->fadeState + 1) / 2;
	}
}

void Fader::FadeToBlack() {
	this->fadeState = 1;
	this->alfa = 0;
}

void Fader::FadeFromBlack() {
	this->fadeState = -1;
	this->alfa = 1;
}