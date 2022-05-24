#ifndef UTILITY_H
#define UTILITY_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <vector>
#include "lodepng.h"

class GUItexture;

const float PI = 3.141592653589793f;

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

enum Scene {
	Error = 0,
	Start = 1,
	Settings = 2,
	Playing = 3,
	Pause = 4,
	Win = 5,
	Loose = 6
};

struct GameState {
	Scene state = Start;
};

struct Button {
	GUItexture* normal;
	GUItexture* highlighted;
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