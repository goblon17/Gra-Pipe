#include "Win.h"

Win::Win(WindowSize* winSize, CursorState* cursor, Camera* camera, int* boardSize) {
	this->logo = new GUItexture("textures/gui/win.png", glm::vec2(0, 0.75), glm::vec2(0.818, 0.2));

	this->buttons.push_back(new Button("textures/gui/next_nor.png", "textures/gui/next_hig.png", glm::vec2(0, -0.1), glm::vec2(0.695, 0.15)));
	this->buttons.push_back(new Button("textures/gui/again_nor.png", "textures/gui/again_hig.png", glm::vec2(0, -0.45), glm::vec2(0.886, 0.15)));
	this->buttons.push_back(new Button("textures/gui/menu_normal.png", "textures/gui/menu_highlight.png", glm::vec2(0, -0.8), glm::vec2(0.368, 0.15)));

	this->boardSize = boardSize;
	this->winSize = winSize;
	this->cursor = cursor;
	this->camera = camera;
}

Win::~Win() {
	delete this->logo;
	for (Button* b : this->buttons) {
		delete b;
	}
}

void Win::Draw(double dTime, ShaderProgram* guiShader) {
	this->logo->Draw(this->camera, guiShader);
	bool f = !(*this->boardSize < 10);
	for (Button* b : this->buttons) {
		if (f) {
			f = false;
			continue;
		}
		b->Draw(this->camera, guiShader);
	}
	this->camera->changePos(dTime * rotationSpeed, 0, 0);
}

void Win::cursorPosCallback(GLFWwindow* window, double xPos, double yPos) {
	bool f = !(*this->boardSize < 10);
	for (Button* b : this->buttons) {
		if (f) {
			f = false;
			continue;
		}
		b->mousePosCallback(window, xPos, yPos, this->winSize);
	}
}

void Win::mouseButtonCallback(GLFWwindow* window, int button, int action, int mods, Game* game) {
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
				if (game->board_size < 10) {
					printf("Następny\n");
					game->increaseSize();
					game->setCurrentState(GAME_SCENE_PLAY);
				}
				break;
			}
			case 1: {
				printf("Jeszcze raz\n");
				game->board->initNewBoard(game->board_size);
				game->setCurrentState(GAME_SCENE_PLAY);
				break;
			}
			case 2: {
				printf("Menu\n");
				game->board->initNewBoard(game->board_size);
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