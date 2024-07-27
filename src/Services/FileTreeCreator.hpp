#pragma once

#include <filesystem>   //  std::filesystem::path, std::filesystem::exists
#include <string>   //  std::string

#include "../DataModel/Folder.hpp"
#include "../DataModel/File.hpp"

class FileTreeCreator {
public:
    FileTreeCreator();
    
    std::string create(const Folder &folder, const std::filesystem::path &path) const;
    std::string create(const File &file, const std::filesystem::path &path) const;
};
