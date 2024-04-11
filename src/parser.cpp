#include "parser.h"

#include <curl/curl.h>
#include <iostream>

typedef size_t(*curl_write)(char*, size_t, size_t, std::string*);

std::string request(std::string location) {
    CURLcode res_code = CURLE_FAILED_INIT;
    
    std::string result;
    std::string url = "https://wttr.in/" + location + "?format=j1";

    CURL * curl = curl_easy_init();

    if (!curl) std::cerr << "Couldn't init curl" << std::endl;

    curl_global_init(CURL_GLOBAL_ALL);

    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, static_cast<curl_write>(
        [](char* contents, size_t size, size_t nmemb, std::string* data) -> size_t {
            size_t new_size = size * nmemb;
            if (data != NULL) { data->append(contents, new_size); return new_size; }
            return 0; 
        }
    ));

    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &result);
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_USERAGENT, "simple scraper");

    res_code = curl_easy_perform(curl);

    if (res_code) {
        std::cerr << "Runtime error: " << curl_easy_strerror(res_code) << std::endl;
    }

    curl_easy_cleanup(curl);
    curl_global_cleanup();

    return result;
}