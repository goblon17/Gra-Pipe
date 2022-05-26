#include "MultipleStateButton.h"

MultipleStateButton::MultipleStateButton(int n, ...) {
	va_list args;
	va_start(args, n);
	for (int i = 0; i < n; i++) {
		this->buttons.push_back(va_arg(args, Button*));
	}
	va_end(args);
}

MultipleStateButton::~MultipleStateButton() {
	for (Button* b : this->buttons) {
		delete b;
	}
}

void MultipleStateButton::Draw(Camera* camera, ShaderProgram* shader) {
	this->buttons.at(this->state)->Draw(camera, shader);
}

void MultipleStateButton::mousePosCallback(GLFWwindow* window, double X, double Y, WindowSize* winSize) {
	this->buttons.at(this->state)->mousePosCallback(window, X, Y, winSize);
	this->isSeleced = this->buttons.at(this->state)->isSeleced;
}

void MultipleStateButton::nextState() {
	this->state = (this->state + 1) % this->buttons.size();
}