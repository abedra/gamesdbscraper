#include <iostream>
#include "json.hpp"
#include "HttpClient.h"
#include "Filesystem.h"

int main() {
    auto api_key = std::getenv("GAMESDB_API_KEY");
    auto roms_path = std::getenv("GAMESDB_ROM_PATH");

    HttpClient client(api_key);
    auto roms = Filesystem::get_files(roms_path);

    auto response = client.get(roms.at(0));
    if (response) {
        auto serialized = nlohmann::json::parse(response.value().body);
        std::cout << serialized << std::endl;
        return 0;
    } else {
        std::cout << "ERROR" << std::endl;
    }
}
