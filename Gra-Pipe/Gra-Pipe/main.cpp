#define GLM_FORCE_RADIANS

#include <cstdio>
#include <cstdlib>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "shaderprogram.h"
#include "Utility.h"
#include "Camera.h"

int WINDOW_WIDTH = 500;
int WINDOW_HEIGHT = 500;

Camera* camera;
ShaderProgram* shader;
CursorPos cursor;

void errorCallback(int error, const char* description) {
	fputs(description, stderr);
}

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {

}

void cursorPosCallback(GLFWwindow* window, double xPos, double yPos) {
	printf("%lf : %lf\n", cursor.curX, cursor.curY);
	cursor.oldX = cursor.curX;
	cursor.oldY = cursor.curY;
	cursor.curX = xPos;
	cursor.curY = yPos;
}

void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
	switch (button) {
	case GLFW_MOUSE_BUTTON_MIDDLE: {
		if (action == GLFW_PRESS) {
			cursor.middle = 1;
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		}
		else if (action == GLFW_RELEASE) {
			cursor.middle = 0;
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		}
		break;
	}
	case GLFW_MOUSE_BUTTON_LEFT: {
		if (action == GLFW_PRESS) {
			cursor.left = 1;
		}
		else if (action == GLFW_RELEASE) {
			cursor.left = 0;
		}
		break;
	}
	case GLFW_MOUSE_BUTTON_RIGHT: {
		if (action == GLFW_PRESS) {
			cursor.right = 1;
		}
		else if (action == GLFW_RELEASE) {
			cursor.right = 0;
		}
		break;
	}
	}
}

void windowResizeCallback(GLFWwindow* window, int width, int height) {
	if (height == 0) return;
	camera->aspectRatio = (float)width / (float)height;
	glViewport(0, 0, width, height);
	WINDOW_WIDTH = width;
	WINDOW_HEIGHT = height;
}

void initOpenGLProgram(GLFWwindow** window) {
	glfwSetErrorCallback(errorCallback);

	if (!glfwInit()) {
		fprintf(stderr, "Nie udalo sie zainicjowac GLFW.\n");
		exit(EXIT_FAILURE);
	}

	*window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "PipeGame", NULL, NULL);

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
		glm::vec3(0, 1, -2.5),	//pozycja kamery
		glm::vec3(0, 0, 0),		//gdzie kamera patrzy
		glm::vec3(0, 1, 0),		//gdzie kamera ma gore
		60,						//fov
		1,						//stosunek szer/wys
		0.1f,					//bliska plaszczyzna
		50);					//daleka plaszczyzna

	glClearColor(1, 0, 1, 1);
	glEnable(GL_DEPTH_TEST);
	glfwSetInputMode(*window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	glfwSetWindowSizeCallback(*window, windowResizeCallback);
	glfwSetKeyCallback(*window, keyCallback);
	glfwSetCursorPosCallback(*window, cursorPosCallback);
	glfwSetMouseButtonCallback(*window, mouseButtonCallback);

	shader = new ShaderProgram("v_shader.glsl", NULL, "f_shader.glsl");
}

void freeOpenGLProgram(GLFWwindow* window) {
	delete shader;
	glfwDestroyWindow(window);
	glfwTerminate();
}

void drawScene(GLFWwindow* window) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glfwSwapBuffers(window);
}

int main() {
	GLFWwindow* window = nullptr;

	initOpenGLProgram(&window);

	while (!glfwWindowShouldClose(window)) {
		drawScene(window);
		glfwPollEvents();
	}

	freeOpenGLProgram(window);

	exit(EXIT_SUCCESS);
}