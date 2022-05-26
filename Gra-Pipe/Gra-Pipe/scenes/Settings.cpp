#include "Settings.h"

Settings::Settings(WindowSize* winSize, CursorState* cursor, Camera* camera) {
	this->logo = new GUItexture("textures/gui/settings_normal.png", glm::vec2(0, 0.75), glm::vec2(0.75, 0.15));

	Button* multButton[5];
	glm::vec2 mPos = glm::vec2(0, -0.45);
	glm::vec2 mSize = glm::vec2(0.75, 0.15);
	for (int i = 0; i < 5; i++) {
		char nor[] = "textures/gui/sens1_nor.png";
		char hig[] = "textures/gui/sens1_hig.png";
		nor[17] += i;
		hig[17] += i;
		multButton[i] = new Button(nor, hig, mPos, mSize);
	}

	this->buttons.push_back(new Button("textures/gui/menu_normal.png", "textures/gui/menu_highlight.png", glm::vec2(0, -0.8), glm::vec2(0.368, 0.15)));
	this->buttons.push_back(new MultipleStateButton(5, multButton[0], multButton[1], multButton[2], multButton[3], multButton[4]));

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
				printf("Czulost: %d\n", this->sensitivity);
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