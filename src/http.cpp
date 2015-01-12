#include <vector>
#include <string>
#include "http.h"
#include "zeppelin.h"
#include <fstream>
#include <iostream>


zep::Http::Http() {
	curl = curl_easy_init();
	status = "";
}

void zep::Http::on(const std::string& event, std::function<void (const std::string& data)> callback) {
    this->eventCallbacks[event].push_back(callback);
}
void zep::Http::fireEvent(const std::string& event, const std::string&  data) {
    if(eventCallbacks[event].size() > 0) {
        for(uint i = 0; i < eventCallbacks[event].size(); i++) {
            eventCallbacks[event][i](data);
        } 
    }
}

void zep::Http::post(const string& url, const map<std::string, std::string>& args) {
    std::string fields = "";
    for(std::map<std::string, std::string>::const_iterator it = args.begin(); it != args.end(); it++) {
        fields += it->first + "=" + it->second + "&";
    }
    fields.pop_back();
    curl_easy_setopt(curl, CURLOPT_POST, 1L);
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, fields.c_str());
    curl_easy_setopt(curl, CURLOPT_USERAGENT, "Zeppelin/0.1");
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, zep::Http::onload);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, static_cast<void*>(this));
    curl_easy_setopt(curl, CURLOPT_WRITEHEADER, static_cast<void*>(this));
    curl_easy_setopt(curl, CURLOPT_HEADERFUNCTION, zep::Http::onheader);		
    curl_easy_perform(curl);	
}
void zep::Http::get(const string& url) {
    curl_easy_setopt(curl, CURLOPT_HTTPGET, 1L);
    curl_easy_setopt(curl, CURLOPT_USERAGENT, "Zeppelin/0.1");
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, zep::Http::onload);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, static_cast<void*>(this));
    curl_easy_setopt(curl, CURLOPT_WRITEHEADER, static_cast<void*>(this));
    curl_easy_setopt(curl, CURLOPT_HEADERFUNCTION, zep::Http::onheader);		
    curl_easy_perform(curl);	
}

void zep::Http::responseHeader(const string& header) {
	size_t colon = header.find(":");
	if(colon == string::npos && header.size() > 12) {
		status = header.substr(9, 3);
	} else {
		if(colon != string::npos) {
			this->responseHeaders[header.substr(0, colon)] = header.substr(colon + 2, header.size() - (colon + 3));
		}
	}
}

size_t zep::Http::onheader(void *contents, size_t size, size_t nmemb, void *userp) {
	Http *http = static_cast<Http*>(userp);
	size_t realsize = size * nmemb;
	string data = string((char*)contents);
	http->responseHeader(data);
    http->fireEvent("header", data);
	return realsize;
}

size_t zep::Http::onload(void *contents, size_t size, size_t nmemb, void *userp) {
	Http *http = static_cast<Http*>(userp);
	size_t realsize = size * nmemb;
	string data = string((char*)contents);
	http->responseText += data;
	//cout << "chunk size: " << realsize << endl;
    http->fireEvent("load", http->responseText);
	return realsize;
}

