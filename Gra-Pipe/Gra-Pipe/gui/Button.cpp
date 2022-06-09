#include "Button.h"

Button::Button(const char* normal_texture, const char* highlighted_texture, glm::vec2 pos, glm::vec2 size) {
	this->normal = new GUItexture(normal_texture, pos, size);
	this->highlighted = new GUItexture(highlighted_texture, pos, size);
	this->pos = pos;
	this->size = size;
	this->isSeleced = false;
}

Button::~Button() {
	delete this->normal;
	delete this->highlighted;
}

void Button::Draw(Camera* camera, ShaderProgram* shader) {
	if (this->isSeleced) {
		this->highlighted->Draw(camera, shader);
	} else {
		this->normal->Draw(camera, shader);
	}
}

bool Button::inBounds(float normalX, float normalY, float ar) {
	float posX = this->pos.x + glm::sign(this->pos.x) * (this->size.x - this->size.x / ar);
	posX *= ar;
	return (normalX < posX + this->size.x) && (normalX > posX - this->size.x) && (normalY < this->pos.y + this->size.y) && (normalY > this->pos.y - this->size.y);
}

void Button::mousePosCallback(GLFWwindow* window, double X, double Y, WindowSize* winSize) {
	float ar = ((float)winSize->width / (float)winSize->height);
	float normalX = ((2 * (float)X / (float)winSize->width) - 1) * ar;
	float normalY = 1 - (2 * (float)Y / (float)winSize->height);
	this->isSeleced = inBounds(normalX, normalY, ar) && glfwGetInputMode(window, GLFW_CURSOR) == GLFW_CURSOR_NORMAL;
}