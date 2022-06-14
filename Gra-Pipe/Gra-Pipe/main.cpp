//--------------------------------------------
// Title: Gra Pipe
// Authors: Szymon Kaczmarek, Lukasz Kania
// Date: ../../2022
// Version: 1.2
//--------------------------------------------

#define GLM_FORCE_RADIANS

#include <windows.h>
#include <cstdio>
#include <cstdlib>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "utility/Utility.h"
#include "utility/lodepng.h"
#include "Game.h"

WindowSize* winSize;

Game* game;

void errorCallback(int error, const char* description) {
	fputs(description, stderr);
}

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	game->keyCallback(window, key, scancode, action, mods);
}

void cursorPosCallback(GLFWwindow* window, double xPos, double yPos) {
	game->cursorPosCallback(window, xPos, yPos);
}

void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
	game->mouseButtonCallback(window, button, action, mods);
}

void scrollCallback(GLFWwindow* window, double xOffset, double yOffset) {
	game->scrollCallback(window, xOffset, yOffset);
}

void windowResizeCallback(GLFWwindow* window, int width, int height) {
	game->windowResizeCallback(window, width, height);
}

void initOpenGLProgram(GLFWwindow** window) {
	glfwSetErrorCallback(errorCallback);

	winSize = new WindowSize{ 500, 500 };

	if (!glfwInit()) {
		fprintf(stderr, "Nie udalo sie zainicjowac GLFW.\n");
		exit(EXIT_FAILURE);
	}

	*window = glfwCreateWindow(winSize->width, winSize->height, "Pipe", NULL, NULL);

	unsigned w, h;
	std::vector<unsigned char> i;
	lodepng::decode(i, w, h, "textures/Logo.png");

	GLFWimage image;
	image.height = h;
	image.width = w;
	image.pixels = (unsigned char*)i.data();

	glfwSetWindowIcon(*window, 1, &image);

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

	game = new Game(winSize);

	glClearColor(0, 0, 0, 1);
	glEnable(GL_DEPTH_TEST);
	glfwSetInputMode(*window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	glfwSetWindowSizeCallback(*window, windowResizeCallback);
	glfwSetKeyCallback(*window, keyCallback);
	glfwSetCursorPosCallback(*window, cursorPosCallback);
	glfwSetMouseButtonCallback(*window, mouseButtonCallback);
	glfwSetScrollCallback(*window, scrollCallback);
}

void freeOpenGLProgram(GLFWwindow* window) {
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