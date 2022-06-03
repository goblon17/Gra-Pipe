#define GLM_FORCE_RADIANS

#include <cstdio>
#include <cstdlib>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "shaderprogram.h"
#include "Camera.h"
#include "Utility.h"
#include "myCube.h"
#include "Board.h"
#include "Game.h"

CursorState* cursor;
WindowSize* winSize;

Game* game;
Camera* camera;

void errorCallback(int error, const char* description) {
	fputs(description, stderr);
}

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	game->keyCallback(window, key, scancode, action, mods);
}

void cursorPosCallback(GLFWwindow* window, double xPos, double yPos) {
	cursor->oldX = cursor->curX;
	cursor->oldY = cursor->curY;
	cursor->curX = xPos;
	cursor->curY = yPos;
	game->cursorPosCallback(window, xPos, yPos);
}

void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
	game->mouseButtonCallback(window, button, action, mods);
}

void scrollCallback(GLFWwindow* window, double xOffset, double yOffset) {
	game->scrollCallback(window, xOffset, yOffset);
}

void windowResizeCallback(GLFWwindow* window, int width, int height) {
	if (height == 0) return;
	camera->resize((float)width / (float)height);
	glViewport(0, 0, width, height);
	winSize->width = width;
	winSize->height = height;
}

void initOpenGLProgram(GLFWwindow** window) {
	glfwSetErrorCallback(errorCallback);

	winSize = new WindowSize{ 500, 500 };

	if (!glfwInit()) {
		fprintf(stderr, "Nie udalo sie zainicjowac GLFW.\n");
		exit(EXIT_FAILURE);
	}

	*window = glfwCreateWindow(winSize->width, winSize->height, "PipeGame", NULL, NULL);

	if (!*window) {
		fprintf(stderr, "Nie udalo sie utworzyc okna.\n");
		exit(EXIT_FAILURE);
	}

	glfwMakeContextCurrent(*window);
	glfwSwapInterval(1);

	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Nie udalo sie zainicjowac GLEW.\n");
		exit(EXIT_FAILURE);
	}

	camera = new Camera(
		glm::vec3(0, 2, -2.5),	//pozycja kamery
		glm::vec3(0, 0, 0),		//gdzie kamera patrzy
		glm::vec3(0, 1, 0),		//gdzie kamera ma gore
		60,						//fov
		1,						//stosunek szer/wys
		0.01f,					//bliska plaszczyzna
		100);					//daleka plaszczyzna

	glClearColor(0, 0, 0, 1);
	glEnable(GL_DEPTH_TEST);
	glfwSetInputMode(*window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	glfwSetWindowSizeCallback(*window, windowResizeCallback);
	glfwSetKeyCallback(*window, keyCallback);
	glfwSetCursorPosCallback(*window, cursorPosCallback);
	glfwSetMouseButtonCallback(*window, mouseButtonCallback);
	glfwSetScrollCallback(*window, scrollCallback);

	cursor = new CursorState;
	game = new Game(winSize, cursor, camera, board_size);
}

void freeOpenGLProgram(GLFWwindow* window) {
	delete cursor;
	delete camera;
	delete winSize;
	delete game;
	glfwDestroyWindow(window);
	glfwTerminate();
}

void drawScene(GLFWwindow* window, double dTime) {
	game->Draw(dTime);

	glfwSwapBuffers(window);
}

int main() {
	GLFWwindow* window = nullptr;

	initOpenGLProgram(&window);
	double time = 0;
	glfwSetTime(0);
	while (!glfwWindowShouldClose(window)) {
		drawScene(window, time);
		time = glfwGetTime();
		glfwSetTime(0);
		glfwPollEvents();
	}

	freeOpenGLProgram(window);

	exit(EXIT_SUCCESS);
}