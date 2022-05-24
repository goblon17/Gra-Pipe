#ifndef MENU_H
#define MENU_H

#include <vector>
#include "GUItexture.h"
#include "Utility.h"
#include "Camera.h"
#include "Button.h"

class Menu
{
private:
	const int START_BUTTON = 1;
	const int SETTINGS_BUTTON = 2;
	const int EXIT_BUTTON = 3;
	std::vector<Button*> buttons;
	GUItexture* logo;
public:
	Menu();
	~Menu();
	void Draw(Camera* camera, ShaderProgram* shader);
	void mousePosCallback(double X, double Y, int Width, int Height);
};

#endif