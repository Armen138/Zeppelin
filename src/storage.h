#ifndef _LOCALSTORAGE_H
#define _LOCALSTORAGE_H

using namespace std;

namespace zep {
    class Storage {
        public:
            Storage(const std::string& place);
            void set(const std::string& key, const std::string& value);
            std::string get(const std::string& key);
        private:
            std::string place;            
    };
}

#endif
