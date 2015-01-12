#ifndef __RESOURCES_H
#define __RESOURCES_H
#include <iostream>
#include <map>
#include "image.h"

namespace zep {
    class Resources {
        public:
            Resources(const std::string& path);
            Image* image(const std::string& id);
        private:
            std::map<std::string, Image*> images;
    };
}

#endif

