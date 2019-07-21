#pragma once

#include <utility>
#include <optional>
#include <curl/curl.h>

struct HttpResponse {
  long statusCode;
  std::string body;
};

class HttpClient {
public:
  explicit HttpClient(std::string  api_key) : api_key_(std::move(api_key)) {}
  std::optional<HttpResponse> get(const std::string &name) const;
private:
  const std::string api_key_;
  std::string make_url(CURL *curl, const std::string &name) const;
};
