#include <iostream>
#include <sstream>
#include <optional>
#include <curl/curl.h>
#include "HttpClient.h"

static size_t callback(void *contents, size_t size, size_t nmemb, void *userp) {
  ((std::string *) userp)->append((char *) contents, size * nmemb);
  return size * nmemb;
}

std::string HttpClient::make_url(CURL *curl, const std::string &name) const {
    std::stringstream ss;
    std::string fields(
            "players,"
            "publishers,"
            "genres,"
            "overview,"
            "last_updated,"
            "rating,"
            "platform,"
            "coop,"
            "youtube,"
            "os,"
            "processor,"
            "ram,"
            "hdd,"
            "video,"
            "sound,"
            "alternates"
    );

    std::string includes("boxart,platform");


    ss << "https://api.thegamesdb.net/Games/ByGameName"
       << "?apikey=" << api_key_
       << "&name=" << curl_easy_escape(curl, name.c_str(), name.length())
       << "&fields=" << curl_easy_escape(curl, fields.c_str(), fields.length())
       << "&include=" << curl_easy_escape(curl, includes.c_str(), includes.length())
       << "&filter[platform]=7";

  return ss.str();
}

std::optional<HttpResponse> HttpClient::get(const std::string &name) const {
  CURLcode res = CURLE_SEND_ERROR;
  std::string buffer;
  long response_code = 0;

  CURL *curl = curl_easy_init();
  if (curl) {
    curl_easy_setopt(curl, CURLOPT_URL, make_url(curl, name).c_str());
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 1);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, callback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &buffer);

    // TODO: wrap in debug conditional
    // curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);

    res = curl_easy_perform(curl);
    if (res != CURLE_OK) {
      // TODO: use a callback
      std::cout << curl_easy_strerror(res) << std::endl;
      curl_easy_cleanup(curl);
      return std::nullopt;
    }

    curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response_code);
    curl_easy_cleanup(curl);
  }

  return std::optional<HttpResponse>({response_code, buffer});
}
