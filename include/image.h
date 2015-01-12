#ifndef __IMAGE_H
#define __IMAGE_H

#include <iostream>
#include <GLFW/glfw3.h>

using namespace std;


typedef unsigned int uint;


namespace zep {
	struct rect {
		float x;
		float y;
		float x2;
		float y2;
	};
	struct size {
		uint width;
		uint height;
	};
	class Image {
	public:
		Image(const string& src = "");
		void load(const string& src);
		std::string getSource();
		GLuint getTexture();
		struct zep::rect mapRectangle(int x, int y, int width, int height);
		//static Image* getInstance(Local<Object> self);
		//static Handle<Value> jsConstructor(const Arguments &args);
		//static Handle<Value> jsGetSource(Local<String> property, const v8::AccessorInfo& info);
		//static void jsSetSource(Local<String> property, Local<Value> value, const AccessorInfo& info);
		//static Handle<Value> jsGetWidth(Local<String> property, const v8::AccessorInfo& info);
		//static void jsSetWidth(Local<String> property, Local<Value> value, const AccessorInfo& info);		
		//static Handle<Value> jsGetHeight(Local<String> property, const v8::AccessorInfo& info);
		//static void jsSetHeight(Local<String> property, Local<Value> value, const AccessorInfo& info);
		
		int width;
		int height;		
	protected:
		std::string source;
		GLuint texture;
	};
};

#endif
