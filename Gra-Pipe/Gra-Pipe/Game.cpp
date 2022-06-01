#include "Game.h"

Game::Game(WindowSize* winSize, CursorState* cursor, Camera* camera, int board_size) {
	this->winSize = winSize;
	this->cursor = cursor;
	this->camera = camera;
	this->guiShader = new ShaderProgram("shaders/gui_v_shader.glsl", NULL, "shaders/gui_f_shader.glsl");
	this->skybox = new Skybox();
	this->scenes.push_back(new Menu(winSize, cursor, camera));
	this->scenes.push_back(new Play(winSize, cursor, camera));
	this->scenes.push_back(new Pause(winSize, cursor, camera));
	this->scenes.push_back(new Settings(winSize, cursor, camera));


	this->board_size = board_size;
	this->board = new Board3D(this->board_size);
}

Game::~Game() {
	delete this->skybox;
	delete this->guiShader;
	for (Scene* s : this->scenes) {
		delete s;
	}
	delete this->board;
}

void Game::setCurrentState(int state) {
	this->currentState = state;
}

void Game::Draw(double dTime) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//zmiany.begin()

	this->board->drawBoard(this->camera, dTime);

	//zmieny.end()

	this->skybox->Draw(this->camera);
	this->scenes.at(this->currentState)->Draw(dTime, this->guiShader);

	glm::mat4 M = glm::mat4(1);
	M = glm::translate(M, this->caclMouseToWorld(0));
	M = glm::scale(M, glm::vec3(0.2, 0.2, 0.2));

	this->board->modelShader->use();
	glUniformMatrix4fv(this->board->modelShader->u("P"), 1, false, glm::value_ptr(this->camera->Pmat));
	glUniformMatrix4fv(this->board->modelShader->u("V"), 1, false, glm::value_ptr(this->camera->Vmat));
	glUniformMatrix4fv(this->board->modelShader->u("M"), 1, false, glm::value_ptr(M));
	glUniform4f(this->board->modelShader->u("color"), 0, 0, 1, 1);

	Models::sphere.drawSolid();
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

glm::vec3 Game::caclMouseToWorld(float y) {
	float mouseX = (this->cursor->curX / this->winSize->width) * 2 - 1;
	float mouseY = (this->cursor->curY / this->winSize->height) * 2 - 1;
	float ar = this->camera->aspectRatio;
	float alfa = this->camera->FOV / 2;
	float fZ = this->camera->farPlane;
	mouseX *= -1;
	mouseY /= ar;
	float fX = glm::tan(alfa) * fZ * ar * mouseX;
	float fY = glm::tan(alfa) * fZ * ar * mouseY;
	glm::vec4 fPos(fX, fY, fZ, 1);
	glm::mat4 invV = glm::inverse(this->camera->Vmat);
	glm::vec3 wPosF = invV * fPos;
	glm::vec3 camPos = this->camera->pos;
	glm::vec3 mouseVector = wPosF - camPos;
	float e = (y - camPos.y) / mouseVector.y;
	mouseVector *= e;
	glm::vec3 pos = camPos + mouseVector;
	return pos;
}