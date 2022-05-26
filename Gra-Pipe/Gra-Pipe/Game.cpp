#include "Game.h"

Game::Game(WindowSize* winSize, CursorState* cursor, Camera* camera) {
	this->winSize = winSize;
	this->cursor = cursor;
	this->camera = camera;
	this->guiShader = new ShaderProgram("shaders/gui_v_shader.glsl", NULL, "shaders/gui_f_shader.glsl");
	this->skybox = new Skybox();
	this->scenes.push_back(new Menu(winSize, cursor, camera));
	this->scenes.push_back(new Play(winSize, cursor, camera));
	this->scenes.push_back(new Pause(winSize, cursor, camera));
	this->scenes.push_back(new Settings(winSize, cursor, camera));
}

Game::~Game() {
	delete this->skybox;
	delete this->guiShader;
	for (Scene* s : this->scenes) {
		delete s;
	}
}

void Game::setCurrentState(int state) {
	this->currentState = state;
}

void Game::Draw(double dTime) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	this->skybox->Draw(this->camera);
	this->scenes.at(this->currentState)->Draw(dTime, this->guiShader);
}

void Game::mouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
	this->scenes.at(this->currentState)->mouseButtonCallback(window, button, action, mods, this);
}

void Game::cursorPosCallback(GLFWwindow* window, double xPos, double yPos) {
	this->scenes.at(this->currentState)->cursorPosCallback(window, xPos, yPos);
}

void Game::scrollCallback(GLFWwindow* window, double xOffset, double yOffset) {
	this->scenes.at(this->currentState)->scrollCallback(window, xOffset, yOffset);
}

void Game::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	this->scenes.at(this->currentState)->keyCallback(window, key, scancode, action, mods);
}