#ifndef __TILED_IMPORTER_
#define __TILED_IMPORTER_
#include <iostream>
#include <vector>
#include <string>
#include "gameobject.h"

typedef unsigned int uint;

namespace zep {

	class Tiled {

		public: 
			Tiled(const std::string& name);
			~Tiled();
			void render();
		private:
			std::vector<uint> data;
			std::vector<Image*> textures;
	};

}
#endif
