#include "Game.h"

Game::Game(WindowSize* winSize) {
	this->winSize = winSize;
	this->board_size = 4;
	this->guiShader = new ShaderProgram("shaders/gui_v_shader.glsl", NULL, "shaders/gui_f_shader.glsl");
	this->skybox = new Skybox();
	this->cursor = new CursorState;
	this->camera = new Camera(
		glm::vec3(0, 2, -2.5),	//pozycja kamery
		glm::vec3(0, 0, 0),		//gdzie kamera patrzy
		glm::vec3(0, 1, 0),		//gdzie kamera ma gore
		60,						//fov
		(float)this->winSize->width / (float)this->winSize->height, //stosunek szer/wys
		0.01f,					//bliska plaszczyzna
		100);					//daleka plaszczyzna

	this->board = new Board3D(this->camera, this->winSize, this->board_size);

	this->scenes.push_back(new Menu(this->winSize, this->cursor, this->camera));
	this->scenes.push_back(new Play(this->winSize, this->cursor, this->camera, this->board));
	this->scenes.push_back(new Pause(this->winSize, this->cursor, this->camera));
	this->scenes.push_back(new Settings(this->winSize, this->cursor, this->camera));
	this->scenes.push_back(new Win(this->winSize, this->cursor, this->camera, &this->board_size));
}

Game::~Game() {
	delete this->skybox;
	delete this->guiShader;
	delete this->cursor;
	for (Scene* s : this->scenes) {
		delete s;
	}
	delete this->board;
	delete this->camera;
}

void Game::setCurrentState(int state) {
	this->currentState = state;
}

void Game::Draw(double dTime) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	this->board->drawBoard(dTime);

	this->skybox->Draw(this->camera);
	this->scenes.at(this->currentState)->Draw(dTime, this->guiShader);
}

void Game::mouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
	this->scenes.at(this->currentState)->mouseButtonCallback(window, button, action, mods, this);
}

void Game::cursorPosCallback(GLFWwindow* window, double xPos, double yPos) {
	this->cursor->oldX = this->cursor->curX;
	this->cursor->oldY = this->cursor->curY;
	this->cursor->curX = xPos;
	this->cursor->curY = yPos;
	this->scenes.at(this->currentState)->cursorPosCallback(window, xPos, yPos);
}

void Game::scrollCallback(GLFWwindow* window, double xOffset, double yOffset) {
	this->scenes.at(this->currentState)->scrollCallback(window, xOffset, yOffset);
}

void Game::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	this->scenes.at(this->currentState)->keyCallback(window, key, scancode, action, mods);
}

void Game::windowResizeCallback(GLFWwindow* window, int width, int height) {
	if (height == 0) return;
	this->camera->resize((float)width / (float)height);
	glViewport(0, 0, width, height);
	this->winSize->width = width;
	this->winSize->height = height;
}

void Game::increaseSize() {
	this->scenes.at(3)->buttons.at(2)->nextState();
	this->board_size = 4 + this->scenes.at(3)->buttons.at(2)->state;
	printf("Wielkosc: %d", this->board_size);
	this->board->initNewBoard(this->board_size);
}