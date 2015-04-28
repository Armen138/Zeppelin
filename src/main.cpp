#include <fstream>
#include <iostream>
#include "zeppelin.h"

using namespace std;
using namespace zep;

/*
 * Zeppelin main
 * Events exposed to client app:
 *   -ready
 *   -draw
 *   -update
 *   -keyup
 *   -keydown
 */
int main(int argc, char* argv[]) {
    Zeppelin *zep = new Zeppelin();
	int x = 100;
	int y = 100;
	std::map<std::string, bool> keyDown;
    Resources *resources = new Resources("data");
	GameObject *object = new GameObject(resources->image("star"));
    zep->on("draw", [&] (void* data) {
		if(keyDown["left"]) {
			x--;
		}
		if(keyDown["right"]) {
			x++;
		}
//        zep->draw(resources->image("star"), x, y, 100, 100);
		zep->draw(object);
    });
    zep->on("keydown", [&] (void *data) {
        KeyEvent *key = (KeyEvent*) data;    
        std::cout   << "key in callback " 
                    << key->code 
                    << "(" << key->name << ")" 
                    << std::endl;
        if(key->name == "escape") {
            zep->exit();
        }
		keyDown[key->name] = true;
    });
	zep->on("keyup", [&] (void *data) {
        KeyEvent *key = (KeyEvent*) data;    
		keyDown[key->name] = false;
	});
    zep->run();
    delete zep;
    return 0;
}
