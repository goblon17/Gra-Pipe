#include "Scene.h"

int Scene::getHighlightedID() {
	for (int i = 0; i < this->buttons.size(); i++) {
		if (this->buttons.at(i)->isSeleced) {
			return i;
		}
	}
	return -1;
}