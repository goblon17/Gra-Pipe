#include "Settings.h"

Settings::Settings(WindowSize* winSize, CursorState* cursor, Camera* camera) {
	this->logo = new GUItexture("textures/gui/settings_normal.png", glm::vec2(0, 0.75), glm::vec2(0.75, 0.15));

	Button* multButton1[5];
	glm::vec2 mPos = glm::vec2(0, -0.45);
	glm::vec2 mSize = glm::vec2(0.75, 0.15);
	for (int i = 0; i < 5; i++) {
		char nor[] = "textures/gui/sens1_nor.png";
		char hig[] = "textures/gui/sens1_hig.png";
		nor[17] += i;
		hig[17] += i;
		multButton1[i] = new Button(nor, hig, mPos, mSize);
	}

	Button* multButton2[7];
	mPos = glm::vec2(0, -0.1);
	mSize = glm::vec2(0.805, 0.15);
	for (int i = 0; i < 7; i++) {
		char nor[] = "textures/gui/size4_nor.png";
		char hig[] = "textures/gui/size4_hig.png";
		nor[17] += i;
		hig[17] += i;
		if (i == 6) {
			multButton2[i] = new Button("textures/gui/size10_nor.png", "textures/gui/size10_hig.png", mPos, mSize);
		}
		else {
			multButton2[i] = new Button(nor, hig, mPos, mSize);
		}
	}

	this->buttons.push_back(new Button("textures/gui/menu_normal.png", "textures/gui/menu_highlight.png", glm::vec2(0, -0.8), glm::vec2(0.368, 0.15)));
	this->buttons.push_back(new MultipleStateButton(5, multButton1[0], multButton1[1], multButton1[2], multButton1[3], multButton1[4]));
	this->buttons.push_back(new MultipleStateButton(7, multButton2[0], multButton2[1], multButton2[2], multButton2[3], multButton2[4], multButton2[5], multButton2[6]));

	this->winSize = winSize;
	this->cursor = cursor;
	this->camera = camera;
}

Settings::~Settings() {
	delete this->logo;
	for (Button* b : this->buttons) {
		delete b;
	}
}

void Settings::Draw(double dTime, ShaderProgram* guiShader) {
	this->logo->Draw(this->camera, guiShader);
	for (Button* b : this->buttons) {
		b->Draw(this->camera, guiShader);
	}
	this->camera->changePos(dTime * rotationSpeed, 0, 0);
}

void Settings::cursorPosCallback(GLFWwindow* window, double xPos, double yPos) {
	for (Button* b : this->buttons) {
		b->mousePosCallback(window, xPos, yPos, this->winSize);
	}
}

void Settings::mouseButtonCallback(GLFWwindow* window, int button, int action, int mods, Game* game) {
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
				printf("Menu\n");
				game->setCurrentState(GAME_SCENE_MENU);
				break;
			}
			case 1: {
				this->buttons.at(1)->nextState();
				this->sensitivity = this->buttons.at(1)->state;
				int nS = this->buttons.at(1)->n;
				printf("Czulost: %d\n", this->sensitivity);
				game->camera->sensitivity = game->camera->maxSensitivity - this->sensitivity * game->camera->maxSensitivity / nS;
				break;
			}
			case 2: {
				this->buttons.at(2)->nextState();
				game->board_size = 4 + this->buttons.at(2)->state;
				printf("Wielkosc: %d\n", game->board_size);
				game->board->initNewBoard(game->board_size);
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