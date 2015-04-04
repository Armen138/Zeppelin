#include <iostream>
#include <fstream>
#include "zeppelin.h"
#include "GLFW/glfw3.h"
#include "keys.h"

using namespace std;
using namespace zep;

/* glue keyboard callback to the zep instance */
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    Zeppelin *zep = (Zeppelin*)glfwGetWindowUserPointer(window);
    if(action == GLFW_PRESS) {
        zep->keyDown(key, mods);
    }
    if(action == GLFW_RELEASE) {
        zep->keyUp(key, mods);
    }
}

void Zeppelin::echoVersion() {
    std::cout << "Zeppelin version " << ZEP_VERSION << std::endl;
    std::cout << "OpenGL version " << glGetString(GL_VERSION) << std::endl;
    std::cout << "GLFW version " << GLFW_VERSION_MAJOR << "." << GLFW_VERSION_MINOR << "." << GLFW_VERSION_REVISION << std::endl;
}


Zeppelin::Zeppelin(int width, int height, bool fullscreen) {
    init(width, height, fullscreen);
}

void Zeppelin::on(const std::string& event, std::function<void (void* data)> callback) {
    std::cout << "register callback" << std::endl;
    this->eventCallbacks[event].push_back(callback);
}

void Zeppelin::keyDown(int key, int mods) {
    KeyEvent* keyEvent = new KeyEvent(key, mods);
    fireEvent("keydown", (void*) keyEvent);
    delete keyEvent;
}

void Zeppelin::keyUp(int key, int mods) {
    KeyEvent* keyEvent = new KeyEvent(key, mods);
    fireEvent("keyup", (void*) keyEvent);
    delete keyEvent;
}

void Zeppelin::exit() {
    glfwSetWindowShouldClose(this->window, 1);
}

void Zeppelin::init(int width, int height, bool fullscreen) {
    if(!glfwInit()) {
        std::cout << "Failed to init glfw" << std::endl;
    }
    if(fullscreen) {
        GLFWmonitor *monitor = glfwGetPrimaryMonitor();
        this->window = glfwCreateWindow(width, height, "Zeppelin", monitor, NULL);
    } else {
        this->window = glfwCreateWindow(width, height, "Zeppelin", NULL, NULL);
    }
    if(!this->window) {
        std::cout << "unable to open window" << endl;
        glfwTerminate();
        return;
    }
    glfwMakeContextCurrent(window);    
    glfwSetWindowUserPointer(window, (void*)this);
    glfwSetKeyCallback(this->window, key_callback);
    //glewInit();
    this->echoVersion();
}

void zep::Zeppelin::setColor(Color* color) {
    glColor4f(float(color->getRed()) / 255.0f, 
              float(color->getGreen()) / 255.0f, 
              float(color->getBlue()) / 255.0f, 
              float(color->getAlpha()) / 255.0f);
}

void Zeppelin::draw(GameObject* gameObject) {
	AABB box = gameObject->getBoundingBox();
	Image* image = gameObject->getImage();
	if(image != NULL) {
		this->draw(image, box.x, box.y, box.width, box.height);
	}
}

void Zeppelin::draw(Image* image, double x, double y, double w, double h) {
    glPushAttrib(GL_COLOR_BUFFER_BIT);
    //glColor4f(1.0f, 1.0f, 1.0f, 1.0f); //(float)this->alpha);
    glBindTexture(GL_TEXTURE_2D, image->getTexture());
    glBegin(GL_QUADS);

    double imageWidth = w;
    double imageHeight = h;
    if(imageWidth == 0) {
        imageWidth = image->width;
    }
    if(imageHeight == 0) {
        imageHeight = image->height;
    }
    glTexCoord2f(0, 0); glVertex2f(x, y);
    glTexCoord2f(0, 1); glVertex2f(x, y + imageHeight);
    glTexCoord2f(1, 1); glVertex2f(x + imageWidth, y + imageHeight);
    glTexCoord2f(1, 0); glVertex2f(x + imageWidth, y);

    glEnd();

    glBindTexture(GL_TEXTURE_2D, 0);
    glPopAttrib();
}

void Zeppelin::draw(Image* image, double x, double y, double sw, double sh, double dx, double dy, double dw, double dh) {
    //glPushAttrib(GL_COLOR_BUFFER_BIT);
    //glColor4f(1.0f, 1.0f, 1.0f, 1.0f); //(float)this->alpha);

    glBindTexture(GL_TEXTURE_2D, image->getTexture());
    glBegin(GL_QUADS);
    zep::rect rectf = image->mapRectangle(x, y, sw, sh);

    glTexCoord2f(rectf.x, rectf.y); glVertex2f(dx, dy);
    glTexCoord2f(rectf.x, rectf.y2); glVertex2f(dx, dy + dh);
    glTexCoord2f(rectf.x2, rectf.y2); glVertex2f(dx + dw, dy + dh);
    glTexCoord2f(rectf.x2, rectf.y); glVertex2f(dx + dw, dy);
    glEnd();

    glBindTexture(GL_TEXTURE_2D, 0);
    //glPopAttrib();
            
}

void Zeppelin::fireEvent(const std::string& event, void* data) {
    if(eventCallbacks[event].size() > 0) {
        for(uint i = 0; i < eventCallbacks[event].size(); i++) {
            eventCallbacks[event][i](data);
        } 
    }
}

void Zeppelin::run() {
    float ratio;
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    ratio = width / (float) height;
    std::cout << width << ", " << height << std::endl;
	glViewport( 0, 0, width, height );

    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glDisable(GL_DEPTH_TEST);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0f, width, height, 0.0f, 0.0f, 1.0f);
	glMatrixMode(GL_MODELVIEW);

    while(!glfwWindowShouldClose(this->window)) {
        glClearColor( 0.0f, 0.0f, 0.0f, 0.0f ); //clear background screen to black
        glClear(GL_COLOR_BUFFER_BIT);
        fireEvent("draw");
        glfwSwapBuffers(this->window);
        glfwPollEvents();
    }
    std::cout << "Cleaning up ... " << std::endl;
    glfwDestroyWindow(this->window);
    glfwTerminate();
}
