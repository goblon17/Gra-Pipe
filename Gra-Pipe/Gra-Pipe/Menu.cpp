#include "Menu.h"

Menu::Menu() {
	this->logo = new GUItexture("textures/gui/logo.png", glm::vec2(0, 0.75), glm::vec2(0.418, 0.2));
	
	Button start;
	start.normal = new GUItexture("textures/gui/start_normal.png", glm::vec2(0, -0.1), glm::vec2(0.368, 0.15));
	start.highlighted = new GUItexture("textures/gui/start_highlight.png", glm::vec2(0, -0.5), glm::vec2(0.368, 0.15));
	this->buttons.push_back(start);

	Button settings;
	settings.normal = new GUItexture("textures/gui/settings_normal.png", glm::vec2(0, -0.45), glm::vec2(0.75, 0.15));
	settings.highlighted = new GUItexture("textures/gui/settings_highlight.png", glm::vec2(0, -0.3), glm::vec2(0.75, 0.15));
	this->buttons.push_back(settings);

	Button quit;
	quit.normal = new GUItexture("textures/gui/quit_normal.png", glm::vec2(0, -0.8), glm::vec2(0.559 , 0.15));
	quit.highlighted = new GUItexture("textures/gui/quit_highlight.png", glm::vec2(0, -0.8), glm::vec2(0.559, 0.15));
	this->buttons.push_back(quit);
}

void Menu::Draw(Camera* camera, ShaderProgram* shader) {
	this->logo->Draw(camera, shader);
	for (Button b : this->buttons) {
		b.normal->Draw(camera, shader);
	}
}