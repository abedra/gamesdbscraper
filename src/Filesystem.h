#pragma once

#include <vector>
#include <string>

class Filesystem {
public:
    static std::vector<std::string> get_files(const std::string& path);
};
