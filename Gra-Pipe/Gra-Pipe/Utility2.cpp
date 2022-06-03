#include "Utility2.h"

glm::vec3 caclMouseToWorld(Camera* camera, WindowSize* winSize, double xPos, double yPos, float y) {
	float mouseX = (xPos / winSize->width) * 2 - 1;
	float mouseY = (yPos / winSize->height) * 2 - 1;
	float ar = camera->aspectRatio;
	float alfa = camera->FOV / 2;
	float fZ = camera->farPlane;
	mouseX *= -1;
	mouseY /= ar;
	float fX = glm::tan(alfa) * fZ * ar * mouseX;
	float fY = glm::tan(alfa) * fZ * ar * mouseY;
	glm::vec4 fPos(fX, fY, fZ, 1);
	glm::mat4 invV = glm::inverse(camera->Vmat);
	glm::vec3 wPosF = invV * fPos;
	glm::vec3 camPos = camera->pos;
	glm::vec3 mouseVector = wPosF - camPos;
	float e = (y - camPos.y) / mouseVector.y;
	mouseVector *= e;
	glm::vec3 pos = camPos + mouseVector;
	return pos;
}