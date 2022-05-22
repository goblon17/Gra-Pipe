#ifndef UTILITY_H
#define UTILITY_H

const float PI = 3.141592653589793f;

struct CursorPos {
	double oldX = 0;
	double oldY = 0;
	double curX = 0;
	double curY = 0;
	bool left = false;
	bool right = false;
	bool middle = false;
};

#endif