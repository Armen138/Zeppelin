//#include "image.h"
#include "stb_image.c"
#include "zeppelin.h"

zep::Image::Image(const std::string& src) {
	source = "";
    if(src != "") {
        this->load(src);
    }
}

string zep::Image::getSource() {
	return source;
}

void zep::Image::load(const string& src) {
	source = src;

	FILE *file = fopen(source.c_str(), "rb");
	if(!file) {
		cout << "Can't open image.\n";
		return;
	}

	int comp;
	unsigned char* data = stbi_load_from_file(file, &width, &height, &comp, 0);

    cout << "img size: " << this->width << "x" << this->height << endl;
	cout << "[load] " << src << endl;
	fclose(file);

    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    GLenum sourceFormat = GL_RGBA;
    switch(comp) {
    	case 1: 
    		sourceFormat = GL_LUMINANCE;
    		break;
    	case 2:
    		sourceFormat = GL_LUMINANCE_ALPHA;
    		break;
    	case 3: 
    		sourceFormat = GL_RGB;
    		break;
    	case 4:
    		sourceFormat = GL_RGBA;
    		break;
    	default: 
	    	cout << "unsupported format, channels: " << comp << endl;
	    	stbi_image_free(data);
	    	return;    		   	
    };
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, sourceFormat, GL_UNSIGNED_BYTE, data);
	stbi_image_free(data);
	glBindTexture(GL_TEXTURE_2D, 0);

    GLenum err;
    while ((err = glGetError()) != GL_NO_ERROR) {
        cerr << "OpenGL error: " << err << endl;
    }	
}

GLuint zep::Image::getTexture() {
	return this->texture;
}

zep::rect zep::Image::mapRectangle(int x, int y, int width, int height) {
	zep::rect rectf;	
	rectf.x = (float)x / (float)this->width;
	rectf.y = (float)y / (float)this->height;
	rectf.x2 = rectf.x + ((float)width / (float)this->width);
	rectf.y2 = rectf.y + ((float)height / (float)this->height);
	return rectf;
}

//zep::Image* zep::Image::getInstance(Local<Object> self) {
	//Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
	//void *ptr = wrap->Value();
	//zep::Image* image = static_cast<Image*>(ptr);
	//return image;
//}

//Handle<Value> zep::Image::jsConstructor(const Arguments &args) {
	//zep::Image* img = new Image();
	//Handle<ObjectTemplate> imageTemplate = ObjectTemplate::New();
	//imageTemplate->SetInternalFieldCount(1);	
	//imageTemplate->SetAccessor(String::New("src"), zep::Image::jsGetSource, zep::Image::jsSetSource);	
	//imageTemplate->SetAccessor(String::New("width"), zep::Canvas::jsGetWidth, 0);
	//imageTemplate->SetAccessor(String::New("height"), zep::Canvas::jsGetHeight, 0);
	//Local<Object> instance = imageTemplate->NewInstance();
	//instance->SetInternalField(0, External::New(img) );
	//return instance;
//}


//Handle<Value> zep::Image::jsGetSource(Local<String> property, const v8::AccessorInfo& info) {
	//zep::Image* image = zep::Image::getInstance(info.Holder());
	//return String::New(image->getSource().c_str());
//}


//void zep::Image::jsSetSource(Local<String> property, Local<Value> value, const AccessorInfo& info) {
	//zep::Image* image = zep::Image::getInstance(info.Holder());
	//String::AsciiValue src(value->ToString());	
	//image->setSource(*src);	
	//Handle<Value> onload = info.Holder()->Get(String::New("onload"));
	//if(!onload->IsUndefined()) {
		//cout << "calling onload\n";
		//zep::eventCallback(onload, Object::New());
	//} else {
		//cout << "no onload defined\n";
	//}
//}


//Handle<Value> zep::Image::jsGetWidth(Local<String> property, const v8::AccessorInfo& info) {
	//Image* canvas = zep::Image::getInstance(info.Holder());
	//return Number::New(canvas->width);
//}


//Handle<Value> zep::Image::jsGetHeight(Local<String> property, const v8::AccessorInfo& info) {
	//Image* canvas = zep::Image::getInstance(info.Holder());
	//return Number::New(canvas->height);
//}

