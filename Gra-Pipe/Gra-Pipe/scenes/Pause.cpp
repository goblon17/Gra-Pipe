#include "Pause.h"

Pause::Pause(WindowSize* winSize, CursorState* cursor, Camera* camera) {
	this->logo = new GUItexture("textures/gui/pause_normal.png", glm::vec2(0, 0.75), glm::vec2(0.45, 0.15));
	this->buttons.push_back(new Button("textures/gui/resume_normal.png", "textures/gui/resume_highlight.png", glm::vec2(0, -0.1), glm::vec2(0.45, 0.15)));
	this->buttons.push_back(new Button("textures/gui/new_game_normal.png", "textures/gui/new_game_highlight.png", glm::vec2(0, -0.45), glm::vec2(0.668, 0.15)));
	this->buttons.push_back(new Button("textures/gui/menu_normal.png", "textures/gui/menu_highlight.png", glm::vec2(0, -0.8), glm::vec2(0.368, 0.15)));

	this->winSize = winSize;
	this->cursor = cursor;
	this->camera = camera;
}

Pause::~Pause() {
	for (Button* b : this->buttons) {
		delete b;
	}
}

void Pause::Draw(double dTime, ShaderProgram* guiShader) {
	this->logo->Draw(this->camera, guiShader);
	for (Button* b : this->buttons) {
		b->Draw(this->camera, guiShader);
	}
}

void Pause::cursorPosCallback(GLFWwindow* window, double xPos, double yPos) {
	for (Button* b : this->buttons) {
		b->mousePosCallback(window, xPos, yPos, this->winSize);
	}
}

void Pause::mouseButtonCallback(GLFWwindow* window, int button, int action, int mods, Game* game) {
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
				printf("Wznow\n");
				game->setCurrentState(GAME_SCENE_PLAY);
				break;
			}
			case 1: {
				printf("Nowa gra\n");
				game->setCurrentState(GAME_SCENE_PLAY);
				break;
			}
			case 2: {
				printf("Menu\n");
				game->setCurrentState(GAME_SCENE_MENU);
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