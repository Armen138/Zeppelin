#include <rapidjson/document.h>
#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>
#include "storage.h"
#include "tiled.h"
#include "image.h"

using namespace zep;
using namespace rapidjson;

Tiled::Tiled(const std::string& name) {
	Storage data = Storage(".");
	std::string json = data.get(name);
	std::cout << json << std::endl;
	Document d;
	d.Parse(json.c_str());

	Value& s = d["layers"];
	Value& tileSets = d["tilesets"]; 
	for(Value::ConstValueIterator tileSetIterator = tileSets.Begin(); tileSetIterator != tileSets.End(); ++tileSetIterator) {
		if(tileSetIterator->HasMember("image")) {
			std::cout << "tileset has image" << std::endl;
			std::cout << tileSetIterator->FindMember("image")->value.GetString() << std::endl;
			textures.push_back(new Image(tileSetIterator->FindMember("image")->value.GetString()));
		}
	}
	
}

Tiled::~Tiled() {

}

/*
void Tiled::load(const string& src) {
	std::string json = storage->get(src);
	Document d;
	d.Parse(json.c_str());
	Value& s = d["layers"];
	
}
*/
