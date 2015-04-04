#include <rapidjson/document.h>
#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>
#include "storage.h"
#include "tiled.h"

using namespace zep;

Tiled::Tiled(Storage storage) {
	this->storage = storage;
}

~Tiled::Tiled() {

}

void Tiled::load(const string& src) {
	std::string json = storage->get(src);
	Document d;
	d.Parse(json.c_str());
	Value& s = d["layers"];
	
}
