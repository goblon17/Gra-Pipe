#ifndef CAMERA_H
#define CAMERA_H

#define GLM_FORCE_RADIANS

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Utility.h"

class Camera
{
private:
	glm::vec3 pos;
	glm::vec3 target;
	glm::vec3 up;

	float FOV;
	float closePlane;
	float farPlane;

	float radius;
	float alfa;
	float beta;
	float resolution;

	int sensitivity = 1;

	glm::vec3 calcPos();
	float calcAlfa();
	float calcBeta();

public:
	glm::mat4 Vmat;
	glm::mat4 Pmat;
	float aspectRatio;

	glm::mat4 calculateVmat();
	glm::mat4 calculatePmat();

	Camera(glm::vec3 pos, glm::vec3 target, glm::vec3 up, float FOV, float aspectRatio, float closePlane, float fatPlane);

	void changePos(double dX, double dY);
	void changePos(double dScroll);
	void resize(float aspectRatio);
};

#endif