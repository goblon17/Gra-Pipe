#ifndef UTILITY_H
#define UTILITY_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <vector>
#include "lodepng.h"

const float PI = 3.141592653589793f;

glm::vec2 north(0, -1);
glm::vec2 east(0, 1);
glm::vec2 south(1, 0);
glm::vec2 west(-1, 0);
glm::vec2 directions[4] = {north, east, south, west};

struct CursorState {
	double oldX = 0;
	double oldY = 0;
	double curX = 0;
	double curY = 0;
	bool left = false;
	bool right = false;
	bool middle = false;
};

struct WindowSize {
	int width;
	int height;
};

enum class Scene {
	Error = 0,
	Menu = 1,
	Settings = 2,
	Playing = 3,
	Pause = 4,
	Win = 5,
	Loose = 6
};

struct GameState {
	Scene scene = Scene::Menu;
	bool allowCameraMovement = false;
};

struct tile {
	std::vector<glm::vec2> dirs;
	int orientation;
};

GLuint readTexture2D(const char* filaname);

GLuint readCubeMapTexture(std::vector<const char*> filenames);

#endif