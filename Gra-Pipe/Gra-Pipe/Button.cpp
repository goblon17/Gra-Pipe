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

bool Button::inBounds(double normalX, double normalY) {
	return (normalX < this->pos.x + this->size.x) && (normalX > this->pos.x - this->size.x) && (normalY < this->pos.y + this->size.y) && (normalY > this->pos.y - this->size.y);
}

void Button::mousePosCallback(double X, double Y, WindowSize* winSize) {
	double normalX = ((2 * X / (double)winSize->width) - 1) * ((double)winSize->width / (double)winSize->height);
	double normalY = 1 - (2 * Y / winSize->height);
	this->isSeleced = inBounds(normalX, normalY);
}