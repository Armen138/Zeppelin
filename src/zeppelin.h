#ifndef _ZEPPELIN_H
#define _ZEPPELIN_H

#define ZEPPELIN_WINDOW true
#include <iostream>
#include <functional>
#include <vector>
#include <string>
#include <map>
#include <GLFW/glfw3.h>
#include "image.h"
#include "keys.h"
#include "http.h"
#include "color.h"
#include "storage.h"
//#include "canvas.h"

using namespace std;

enum TIMEOUTTYPE {
	TIMEOUT,
	INTERVAL,
	ANIMATIONFRAME
};

#ifndef uint
typedef unsigned int uint;
#endif

namespace zep {
    struct KeyEvent {
        KeyEvent(int key, int mods) {
            this->code = key;
            this->shift = mods & GLFW_MOD_SHIFT;
            this->ctrl = mods & GLFW_MOD_CONTROL;
            this->alt = mods & GLFW_MOD_ALT;
            this->super = mods & GLFW_MOD_SUPER;
            if(keys.find(key) != keys.end()) {
                this->name = keys[key];
            } else {
                this->name = "unknown";
            }
        }
        int code;
        std::string name;
        bool shift;
        bool ctrl;
        bool alt;
        bool super;
    };

    class Zeppelin {
        public:
        Zeppelin(int width = 800, int height = 600, bool fullscreen = false);
        ~Zeppelin() {};
        void keyDown(int key, int mods);
        void keyUp(int key, int mods);
        void run();
        void on(const std::string& event, std::function<void (void* data)> callback);
        void fireEvent(const std::string& event, void* data = NULL);
        void setColor(Color* color);
        void draw(Image* image, double x, double y, double width = 0, double height = 0);
        void draw(Image* image, double x, double y, double sw, double sh, double dx, double dy, double dw, double dh);
        void exit();
        private:
        void init(int width, int height, bool fullscreen);
        void echoVersion();
        std::map<std::string, std::vector<std::function<void (void* data)> > > eventCallbacks;
        GLFWwindow *window;
    };
	//void init();
	//int64_t now();
	//void run(const string& filename);
	//void loop(const string& filename, bool fullscreen = false);
};

#endif
