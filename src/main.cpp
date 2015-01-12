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
    Http *http = new Http();
    Zeppelin *zep = new Zeppelin();
    //Image *star = new Image("assets/images/star.png");
    Color *color = new Color("#5500FF");
    Resources *resources = new Resources("data");
    Storage *storage = new Storage("peep");
    storage->set("test1", "some information");
    zep->setColor(color);
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
    http->on("load", [&] (const std::string& response) {
        std::cout << "load complete" << std::endl;
        storage->set("index.html", response);
    });
    http->on("header", [&] (const std::string& header) {
        std::cout << "header received " << header << std::endl;
    });
    http->post("http://armen138.me/index.html", { 
            { "test", "info" }, 
            { "test2", "testinfo"}  
        });
    zep->run();
    delete zep;
    return 0;
}
