#ifndef UTILITY_H
#define UTILITY_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <vector>
#include "lodepng.h"

const float PI = 3.141592653589793f;
const double rotationSpeed = PI;

const float tile_sphere_radius = 0.08f;
const int tile_sphere_meridians = 20;
const int tile_sphere_parallels = 20;
const float tile_pipe_up_base_radius = 0.05f;
const float tile_pipe_down_base_radius = 0.05f;
const float tile_pipe_height = 0.2f;
const int tile_pipe_sectors = 20;
const int tile_pipe_stacks = 1;
const bool tile_pipe_smooth = 1;
const float tile_pipe_center_shift = 0.15f;
const float model_size = 2.0f * (tile_pipe_height + tile_pipe_center_shift - tile_pipe_height * 0.5f);

const int GAME_SCENE_MENU = 0;
const int GAME_SCENE_PLAY = 1;
const int GAME_SCENE_PAUSE = 2;
const int GAME_SCENE_SETTINGS = 3;
const int GAME_SCENE_WIN = 4;

const int MAX_BOARD_SIZE = 10;

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
	bool isHighlighted;

	tile() { this->x = this->y = this->currentValue = this->visited = this->correctValue = this->isTarget = this->isSource = this->isHighlighted = 0; }
	tile(unsigned int x, unsigned int y) { this->x = x; this->y = y; this->currentValue = this->visited = this->correctValue = this->isTarget = this->isSource = this->isHighlighted = 0; }
	tile(unsigned int x, unsigned int y, unsigned int v, bool vis) { this->x = x; this->y = y; this->currentValue = v; this->visited = vis; this->correctValue = this->isTarget = this->isSource = this->isHighlighted = 0; }
};

GLuint readTexture2D(const char* filaname);

GLuint readCubeMapTexture(std::vector<const char*> filenames);

#endif