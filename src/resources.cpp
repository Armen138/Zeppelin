#include <rapidjson/document.h>
#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>
#include "resources.h"
#include "storage.h"
#include "tiled.h"

using namespace zep;
using namespace rapidjson;

Resources::Resources(const std::string& path) {
    Storage data = Storage(path);
    std::string json = data.get("resources.json");
    Document d;
    d.Parse(json.c_str());
    Value& s = d["images"];
    for(Value::ConstMemberIterator iterator = s.MemberBegin(); iterator != s.MemberEnd(); ++iterator) {
        std::cout << iterator->name.GetString() << " :: " << iterator->value.GetString() << std::endl;
        images[iterator->name.GetString()] = new Image(iterator->value.GetString());
    }

	Value& maps = d["maps"];
	for(Value::ConstMemberIterator mapIterator = maps.MemberBegin(); mapIterator != maps.MemberEnd(); ++mapIterator) {
		std::cout << mapIterator->name.GetString() << " :: " << mapIterator->value.GetString() << std::endl;
		Tiled *map = new Tiled(mapIterator->value.GetString());
	}
}
    
Image* Resources::image(const std::string& id) {
    return images[id];
}
