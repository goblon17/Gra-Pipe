#include "Play.h"

Play::Play(WindowSize* winSize, CursorState* cursor, Camera* camera, Board3D* board) {
	this->logo = nullptr;
	this->buttons.push_back(new Button("textures/gui/pause_normal.png", "textures/gui/pause_highlight.png", glm::vec2(0.55, 0.85), glm::vec2(0.45, 0.15)));

	this->winSize = winSize;
	this->cursor = cursor;
	this->camera = camera;
	this->board = board;
}

Play::~Play() {
	for (Button* b : this->buttons) {
		delete b;
	}
}

void Play::Draw(double dTime, ShaderProgram* guiShader) {
	for (Button* b : this->buttons) {
		b->Draw(camera, guiShader);
	}
}

void Play::cursorPosCallback(GLFWwindow* window, double xPos, double yPos) {
	for (Button* b : this->buttons) {
		b->mousePosCallback(window, xPos, yPos, this->winSize);
	}
	if (this->getHighlightedID() == -1) {
		this->board->cursorPosCallback(window, xPos, yPos);
	}
	else {
		this->board->flushSelection();
	}
	if (this->cursor->middle) {
		camera->changePos(this->cursor->curX - this->cursor->oldX, this->cursor->curY - this->cursor->oldY, 1);
	}
}

void Play::mouseButtonCallback(GLFWwindow* window, int button, int action, int mods, Game* game) {
	switch (button) {
	case GLFW_MOUSE_BUTTON_MIDDLE: {
		if (action == GLFW_PRESS) {
			cursor->middle = 1;
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		}
		else if (action == GLFW_RELEASE) {
			cursor->middle = 0;
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
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
				printf("Pauza\n");
				game->setCurrentState(GAME_SCENE_PAUSE);
				break;
			}
			case -1: {
				if (glfwGetInputMode(window, GLFW_CURSOR) != GLFW_CURSOR_NORMAL) {
					break;
				}
				printf("Plansza\n");
				this->board->leftMouseButton();
				if (this->board->isWon) {
					game->setCurrentState(GAME_SCENE_WIN);
				}
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
			int id = this->getHighlightedID();
			switch (id) {
			case -1: {
				if (glfwGetInputMode(window, GLFW_CURSOR) != GLFW_CURSOR_NORMAL) {
					break;
				}
				printf("azsnalP\n");
				this->board->rightMouseButton();
				if (this->board->isWon) {
					game->setCurrentState(GAME_SCENE_WIN);
				}
				break;
			}
			}
		}
		break;
	}
	}
}

void Play::scrollCallback(GLFWwindow* window, double xOffset, double yOffset) {
	camera->changePos((float)yOffset);
}