#pragma once

#include <optional>

struct HttpResponse {
  long statusCode;
  std::string body;
};

class HttpClient {
public:
  HttpClient(std::string api_key) : api_key_(api_key) {}
  std::optional<HttpResponse> get(const std::string &name) const;
private:
  std::string api_key_;
  std::string make_url(const std::string &name) const;
};
