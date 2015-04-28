#include <iostream>
#include <fstream>
#include <sys/stat.h>
#include "storage.h"

struct stat sb;
zep::Storage::Storage(const std::string& place) {
    if (stat(place.c_str(), &sb) != 0 || !S_ISDIR(sb.st_mode)) {
        mkdir(place.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
    }
    this->place = place;
}

void zep::Storage::set(const std::string& property, const std::string& value) {
	string fileName =  place + "/"  + property;
	ofstream outfile(fileName);
	outfile << value;
	outfile.close();
}

std::string zep::Storage::get(const std::string& property) {
	ifstream file;
	string fileName =  place + "/" + property;
	std::cout << "fetching data from " << fileName << std::endl;
	file.open(fileName.c_str());
	string data((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
	file.close();
	return data;
}

//std::string& zep::Storage::operator[] (const std::string& key) {
    //return this->get(key);
//}
