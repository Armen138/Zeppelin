#include <rapidjson/document.h>
#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>
#include "resources.h"
#include "storage.h"

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
}
    
Image* Resources::image(const std::string& id) {
    return images[id];
}
