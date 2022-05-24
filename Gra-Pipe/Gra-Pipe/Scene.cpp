#include "Scene.h"

void Scene::Draw(Camera* camera, ShaderProgram* shader) {
	this->logo->Draw(camera, shader);
	for (Button* b : this->buttons) {
		b->Draw(camera, shader);
	}
}

int Scene::getHighlightedID() {
	for (int i = 0; i < this->buttons.size(); i++) {
		if (this->buttons.at(i)->isSeleced) {
			return i;
		}
	}
	return -1;
}