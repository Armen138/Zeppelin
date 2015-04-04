#include "gameobject.h"

using namespace std;
using namespace zep;

GameObject::GameObject(zep::Image *image) {
	this->image = image;
	this->boundingBox.x = 0;
	this->boundingBox.y = 0;
	this->boundingBox.width = 32;
	this->boundingBox.height = 32;
};



