#include <filesystem>
#include <iostream>
#include "Filesystem.h"

std::vector<std::string> Filesystem::get_files(const std::string& path) {
    std::vector<std::string> files;
    for (auto &file : std::filesystem::directory_iterator(path)) {
        files.push_back(file.path().stem());
    }
    return files;
}
