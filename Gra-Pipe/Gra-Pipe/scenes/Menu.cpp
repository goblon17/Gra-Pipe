#include "Menu.h"

Menu::Menu(WindowSize* winSize, CursorState* cursor, Camera* camera) {
	this->logo = new GUItexture("textures/gui/logo.png", glm::vec2(0, 0.75), glm::vec2(0.418, 0.2));

	this->buttons.push_back(new Button("textures/gui/start_normal.png", "textures/gui/start_highlight.png", glm::vec2(0, -0.1), glm::vec2(0.368, 0.15)));
	this->buttons.push_back(new Button("textures/gui/settings_normal.png", "textures/gui/settings_highlight.png", glm::vec2(0, -0.45), glm::vec2(0.75, 0.15)));
	this->buttons.push_back(new Button("textures/gui/quit_normal.png", "textures/gui/quit_highlight.png", glm::vec2(0, -0.8), glm::vec2(0.559, 0.15)));
	
	this->winSize = winSize;
	this->cursor = cursor;
	this->camera = camera;
}

Menu::~Menu() {
	delete this->logo;
	for (Button* b : this->buttons) {
		delete b;
	}
}

void Menu::Draw(double dTime, ShaderProgram* guiShader) {
	this->logo->Draw(this->camera, guiShader);
	for (Button* b : this->buttons) {
		b->Draw(this->camera, guiShader);
	}
	this->camera->changePos(dTime * rotationSpeed, 0, 0);
}

void Menu::cursorPosCallback(GLFWwindow* window, double xPos, double yPos) {
	for (Button* b : this->buttons) {
		b->mousePosCallback(window, xPos, yPos, this->winSize);
	}
}

void Menu::mouseButtonCallback(GLFWwindow* window, int button, int action, int mods, Game* game) {
	switch (button) {
	case GLFW_MOUSE_BUTTON_MIDDLE: {
		if (action == GLFW_PRESS) {
			cursor->middle = 1;
		}
		else if (action == GLFW_RELEASE) {
			cursor->middle = 0;
		}
		break;
	}
	case GLFW_MOUSE_BUTTON_LEFT: {
		if (action == GLFW_PRESS) {
			cursor->left = 1;
		}
		else if (action == GLFW_RELEASE) {
			cursor->left = 0;
			int id = this->getHighlightedID();
			switch (id) {
			case 0: {
				printf("Granie\n");
				game->setCurrentState(GAME_SCENE_PLAY);
				break;
			}
			case 1: {
				printf("Ustawienia\n");
				game->setCurrentState(GAME_SCENE_SETTINGS);
				break;
			}
			case 2: {
				glfwSetWindowShouldClose(window, 1);
				break;
			}
			}
		}
		break;
	}
	case GLFW_MOUSE_BUTTON_RIGHT: {
		if (action == GLFW_PRESS) {
			cursor->right = 1;
		}
		else if (action == GLFW_RELEASE) {
			cursor->right = 0;
		}
		break;
	}
	}
}