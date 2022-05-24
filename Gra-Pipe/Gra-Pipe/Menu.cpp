#include "Menu.h"

Menu::Menu() {
	this->logo = new GUItexture("textures/gui/logo.png", glm::vec2(0, 0.75), glm::vec2(0.418, 0.2));

	this->buttons.push_back(new Button("textures/gui/start_normal.png", "textures/gui/start_highlight.png", glm::vec2(0, -0.1), glm::vec2(0.368, 0.15)));
	this->buttons.push_back(new Button("textures/gui/settings_normal.png", "textures/gui/settings_highlight.png", glm::vec2(0, -0.45), glm::vec2(0.75, 0.15)));
	this->buttons.push_back(new Button("textures/gui/quit_normal.png", "textures/gui/quit_highlight.png", glm::vec2(0, -0.8), glm::vec2(0.559, 0.15)));
}

Menu::~Menu() {
	delete this->logo;
	for (Button* b : this->buttons) {
		delete b;
	}
}

void Menu::Draw(Camera* camera, ShaderProgram* shader) {
	this->logo->Draw(camera, shader);
	for (Button* b : this->buttons) {
		b->Draw(camera, shader);
	}
}

void Menu::mousePosCallback(double X, double Y, int Width, int Height) {
	for (Button* b : this->buttons) {
		b->mousePosCallback(X, Y, Width, Height);
	}
}