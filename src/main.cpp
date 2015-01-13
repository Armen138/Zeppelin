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
    //Color *color = new Color("#5500FF");
    Resources *resources = new Resources("data");
    //zep->setColor(color);
    zep->on("draw", [&] (void* data) {
        zep->draw(resources->image("star"), 100, 100, 100, 100);
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
    });
    zep->run();
    delete zep;
    return 0;
}
