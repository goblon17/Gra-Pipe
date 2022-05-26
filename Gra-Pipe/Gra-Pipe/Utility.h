#ifndef UTILITY_H
#define UTILITY_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <vector>
#include "lodepng.h"

const float PI = 3.141592653589793f;

const double rotationSpeed = PI;

const int GAME_SCENE_MENU = 0;
const int GAME_SCENE_PLAY = 1;
const int GAME_SCENE_PAUSE = 2;
const int GAME_SCENE_SETTINGS = 3;
const int GAME_SCENE_WIN = 4;

const glm::vec2 north(0, -1);
const glm::vec2 east(0, 1);
const glm::vec2 south(1, 0);
const glm::vec2 west(-1, 0);
const glm::vec2 directions[4] = {north, east, south, west};

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

struct tile {
	int x, y;
	unsigned int currentValue;
	bool visited;
	unsigned int correctValue;
	bool isTarget;
	bool isSource;

	tile() { this->x = this->y = this->currentValue = this->visited = this->correctValue = this->isTarget = this->isSource = 0; }
	tile(unsigned int x, unsigned int y) { this->x = x; this->y = y; this->currentValue = this->visited = this->correctValue = this->isTarget = this->isSource = 0; }
	tile(unsigned int x, unsigned int y, unsigned int v, bool vis) { this->x = x; this->y = y; this->currentValue = v; this->visited = vis; this->correctValue = this->isTarget = this->isSource = 0; }
};

GLuint readTexture2D(const char* filaname);

GLuint readCubeMapTexture(std::vector<const char*> filenames);

#endif