#include "Camera.h"

Camera::Camera(glm::vec3 pos, glm::vec3 target, glm::vec3 up, float FOV, float aspectRatio, float closePlane, float farPlane) {
	this->pos = pos;
	this->target = target;
	this->up = up;
	this->FOV = FOV * PI / 180.0f;
	this->aspectRatio = aspectRatio;
	this->closePlane = closePlane;
	this->farPlane = farPlane;
	this->Vmat = this->calculateVmat();
	this->Pmat = this->calculatePmat();

	this->radius = glm::distance(pos, target);
	this->alfa = this->calcAlfa();
	this->beta = this->calcBeta();
	this->resolution = 180;
}

glm::mat4 Camera::calculateVmat() {
	return glm::lookAt(
		this->pos,
		this->target,
		this->up
	);
}

glm::mat4 Camera::calculatePmat() {
	return glm::perspective(this->FOV, this->aspectRatio, this->closePlane, this->farPlane);
}

glm::vec3 Camera::calcPos() {
	float x = this->target.x + this->radius * glm::cos(this->alfa) * glm::cos(this->beta);
	float y = this->target.y + this->radius * glm::sin(this->beta);
	float z = this->target.z + this->radius * glm::sin(this->alfa) * glm::cos(this->beta);
	return glm::vec3(x, y, z);
}

float Camera::calcAlfa() {
	float sinB = (this->pos.y - this->target.y) / this->radius;
	float cosB = glm::sqrt(1 - sinB * sinB);
	float sinA = (this->pos.z - this->target.z) / (this->radius * cosB);
	return glm::asin(sinA);
}

float Camera::calcBeta() {
	float sinB = (this->pos.y - this->target.y) / this->radius;
	return glm::asin(sinB);
}

void Camera::changePos(double dX, double dY, int withSens) {
	double dA = dX * PI / 180.0f / this->sensitivity;
	dA *= withSens ? 1 : this->sensitivity;

	this->alfa += dA;
	if (this->alfa > PI) {
		this->alfa -= 2 * PI;
	}
	else if (this->alfa < -PI) {
		this->alfa += 2 * PI;
	}

	double dB = dY * PI / 180.0f / this->sensitivity;
	dB *= withSens ? 1 : this->sensitivity;
	if (this->beta + dB > -PI / 2 && this->beta + dB < PI / 2) {
		this->beta += dB;
	}

	this->pos = this->calcPos();
	this->Vmat = this->calculateVmat();
}

void Camera::changePos(double dScroll) {
	this->radius -= dScroll;
	this->pos = this->calcPos();
	this->Vmat = this->calculateVmat();
}

void Camera::resize(float aspectRatio) {
	this->aspectRatio = aspectRatio;
	this->Pmat = this->calculatePmat();
}