#pragma once

#include <string>   //  std::string
#include <vector>   //  std::vector
#include <variant>  //  std::variant

#include "File.hpp"

class Folder {
public:
    using FileSystemEntity = std::variant<Folder, File>;

    std::string name;
    std::vector<FileSystemEntity> contents;
};
