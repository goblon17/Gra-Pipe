#ifndef UTILITY_H
#define UTILITY_H

#include <GL/glew.h>
#include <vector>
#include "lodepng.h"

const float PI = 3.141592653589793f;

struct CursorState {
	double oldX = 0;
	double oldY = 0;
	double curX = 0;
	double curY = 0;
	bool left = false;
	bool right = false;
	bool middle = false;
};

enum Scene {
	Error = 0,
	Menu = 1,
	Settings = 2,
	Playing = 3,
	Pause = 4,
	Win = 5,
	Loose = 6
};

struct GameState {
	Scene state = Menu;
};

GLuint readTexture2D(const char* filaname);

GLuint readCubeMapTexture(std::vector<const char*> filenames);

#endif