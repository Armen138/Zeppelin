#include <GLFW/glfw3.h>
#include "color.h"

zep::Color::Color(const std::string& colorcode){
    set(colorcode);
}

void zep::Color::set(const std::string& colorcode) {
    asGiven = colorcode;
    if(colorcode[0] == '#'){
            red = (unsigned char)(unhex(colorcode[1]) * 16 + unhex(colorcode[2]));
            green = (unsigned char)(unhex(colorcode[3]) * 16 + unhex(colorcode[4]));
            blue = (unsigned char)(unhex(colorcode[5]) * 16 + unhex(colorcode[6]));
            alpha = 255;
    }
    else if(colorcode.substr(0, 3) == "rgb"){
            //strip whitespace and other irrelevant parts of the string
            std::string rgbacolor = colorcode;
            unsigned int bracket = rgbacolor.find('(');
            rgbacolor.erase(0, bracket + 1);
            bracket = rgbacolor.find(')');
            rgbacolor.erase(bracket);
            for(unsigned int i = rgbacolor.size(); i > 0; --i){
                    if(rgbacolor[i]== ' ') rgbacolor.erase(i, 1);
            }
            double comma = rgbacolor.find(',');
            double lastcomma = 0;
            red = (unsigned char) atoi(rgbacolor.substr(lastcomma, comma).c_str());
            lastcomma = comma + 1;
            comma = rgbacolor.find(',', lastcomma);
            green = (unsigned char) atoi(rgbacolor.substr(lastcomma, comma).c_str());
            lastcomma = comma + 1;
            comma = rgbacolor.find(',', lastcomma);
            blue = (unsigned char) atoi(rgbacolor.substr(lastcomma, comma).c_str());

            if(comma != std::string::npos) { // got alpha value
                    lastcomma = comma + 1;
                    float alphaf = atof(rgbacolor.substr(lastcomma).c_str());
                    alpha = (unsigned char)(alphaf * 255.0f);
            }
            else{
                    alpha = 255;
            }
    }
    else{
            if(colorcode == "black"){ red = 0; green = 0; blue = 0; alpha = 255; }
            if(colorcode == "white"){ red = 255; green = 255; blue = 255; alpha = 255; }
    }
    // cout << "color: " << int(red) << ", " << int(green) << ", " << int(blue) << ", " << int(alpha) << endl;
}

int zep::Color::unhex(unsigned char hex)
{
    if(hex < 64) return hex - 48;
    if(hex < 96) return hex - 55;
    return hex - 87;
}
