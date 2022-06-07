#include "Scene.h"

int Scene::getHighlightedID() {
	for (size_t i = 0; i < this->buttons.size(); i++) {
		if (this->buttons.at(i)->isSeleced) {
			return i;
		}
	}
	return -1;
}