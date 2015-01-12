#ifndef _COLOR_H
#define _COLOR_H
#include <iostream>
#include <stdlib.h>

using namespace std;
namespace zep {
	class Color {
	    public:
	        Color(const std::string& colorcode = "#FFFFFF");
	        unsigned char getRed(){ return red; }
	        unsigned char getGreen(){ return green; }
	        unsigned char getBlue(){ return blue; }
	        unsigned char getAlpha(){ return alpha; }
	        std::string toString(){ return asGiven; }
	        void set(const std::string& colorcode);
        private:
	       	std::string asGiven;
	        int unhex(unsigned char hex);
	        unsigned char red;
	        unsigned char green;
	        unsigned char blue;
	        unsigned char alpha;
	};
};
#endif
