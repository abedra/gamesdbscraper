#include <iostream>
#include "json.hpp"
#include "HttpClient.h"

int main() {
  auto api_key = std::getenv("GAMESDB_API_KEY");
  HttpClient client(api_key);
  auto response = client.get("Metroid");
  if (response) {
    auto serialized = nlohmann::json::parse(response.value().body);
    std::cout << serialized["code"] << " : " << serialized["status"] << std::endl;
  } else {
    std::cout << "ERROR" << std::endl;
  }
}
