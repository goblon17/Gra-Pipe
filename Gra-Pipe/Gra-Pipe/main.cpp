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
#include "Skybox.h"
#include "myCube.h"
#include "Board.h"
#include "Scene.h"
#include "Menu.h"

CursorState* cursor;
WindowSize* winSize;

Camera* camera;
Skybox* skybox;
Menu* menu;
ShaderProgram* shader;
ShaderProgram* guiShader;

void errorCallback(int error, const char* description) {
	fputs(description, stderr);
}

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {

}

void cursorPosCallback(GLFWwindow* window, double xPos, double yPos) {
	cursor->oldX = cursor->curX;
	cursor->oldY = cursor->curY;
	cursor->curX = xPos;
	cursor->curY = yPos;
	menu->cursorPosCallback(window, xPos, yPos);
}

void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
	menu->mouseButtonCallback(window, button, action, mods);
}

void scrollCallback(GLFWwindow* window, double xOffset, double yOffset) {
	camera->changePos(yOffset);
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
		glm::vec3(0, 1, -2.5),	//pozycja kamery
		glm::vec3(0, 0, 0),		//gdzie kamera patrzy
		glm::vec3(0, 1, 0),		//gdzie kamera ma gore
		60,						//fov
		1,						//stosunek szer/wys
		0.01f,					//bliska plaszczyzna
		100);					//daleka plaszczyzna

	skybox = new Skybox();

	glClearColor(0, 0, 0, 1);
	glEnable(GL_DEPTH_TEST);
	glfwSetInputMode(*window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	glfwSetWindowSizeCallback(*window, windowResizeCallback);
	glfwSetKeyCallback(*window, keyCallback);
	glfwSetCursorPosCallback(*window, cursorPosCallback);
	glfwSetMouseButtonCallback(*window, mouseButtonCallback);
	glfwSetScrollCallback(*window, scrollCallback);

	cursor = new CursorState;
	shader = new ShaderProgram("shaders/v_shader.glsl", NULL, "shaders/f_shader.glsl");
	guiShader = new ShaderProgram("shaders/gui_v_shader.glsl", NULL, "shaders/gui_f_shader.glsl");

	menu = new Menu(winSize, cursor);
}

void freeOpenGLProgram(GLFWwindow* window) {
	delete cursor;
	delete shader;
	delete skybox;
	delete camera;
	delete menu;
	delete winSize;
	glfwDestroyWindow(window);
	glfwTerminate();
}

void drawScene(GLFWwindow* window) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	shader->use();

	glm::mat4 M = glm::mat4(1);

	glUniformMatrix4fv(shader->u("P"), 1, false, glm::value_ptr(camera->Pmat));
	glUniformMatrix4fv(shader->u("V"), 1, false, glm::value_ptr(camera->Vmat));
	glUniformMatrix4fv(shader->u("M"), 1, false, glm::value_ptr(M));

	glUniform4f(shader->u("Color"), 1, 1, 1, 1);

	glEnableVertexAttribArray(shader->a("Vertex"));
	glVertexAttribPointer(shader->a("Vertex"), 4, GL_FLOAT, false, 0, myCubeVertices);

	glDrawArrays(GL_TRIANGLES, 0, myCubeVertexCount);

	glDisableVertexAttribArray(shader->a("Vertex"));

	skybox->Draw(camera);

	menu->Draw(camera, guiShader);

	glfwSwapBuffers(window);
}

int main() {
	//init board
	/*Board b(3);
	b.generate();
	b.printBoard();*/

	GLFWwindow* window = nullptr;

	initOpenGLProgram(&window);

	while (!glfwWindowShouldClose(window)) {
		drawScene(window);
		glfwPollEvents();
	}

	freeOpenGLProgram(window);

	exit(EXIT_SUCCESS);
}