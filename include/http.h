#ifndef _XHR_H
#define _XHR_H
#include <curl/curl.h>
#include <functional>
#include <map>

using namespace std;

namespace zep {
	class Http {
	public:
		Http();
		void get(const string& url);
		void post(const string& url, const map<string, string>& args);
		void send();
		void responseHeader(const string& header);
		static size_t onheader(void *contents, size_t size, size_t nmemb, void *userp);
		static size_t onload(void *contents, size_t size, size_t nmemb, void *userp);
        void on(const std::string& event, std::function<void (const std::string& data)> callback);
        void fireEvent(const std::string& event, const std::string& data = "");
	private:
		CURL *curl;
		string status;
		string responseText;
		map<string, string> responseHeaders;
        std::map<std::string, std::vector<std::function<void (const std::string& data)> > > eventCallbacks;
	};
};

#endif
