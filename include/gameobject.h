#ifndef __GAMEOBJECT_H
#define __GAMEOBJECT_H

#include "image.h"

namespace zep {
	struct AABB {
		int x;
		int y;
		int width;
		int height;
	};
	class GameObject {
		public:
			GameObject(zep::Image *image);
			GameObject() { this->image = NULL; };
			~GameObject() {};
			void rotate(double rad);
			AABB getBoundingBox() { return this->boundingBox; };
			Image* getImage() { return this->image; };
		private:
			Image* image;
			AABB boundingBox;
	};
}

#endif

