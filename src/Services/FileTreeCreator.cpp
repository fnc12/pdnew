#include "FileTreeCreator.hpp"

#include <fstream>  //  std::ofstream

FileTreeCreator::FileTreeCreator() = default;

std::string FileTreeCreator::create(const Folder &folder, const std::filesystem::path &path) const {
    const auto folderPath = path / folder.name;
    if (std::filesystem::exists(folderPath)) {
        return "folder exists at path '" + folderPath.string() + "'";
    }
    std::filesystem::create_directory(folderPath);
    for (auto &folderContent : folder.contents) {
        auto errorText = std::visit([this, &folderPath] (const auto &value) {
            return this->create(value, folderPath);
        }, folderContent);
        if (!errorText.empty()) {
            return errorText;
        }
    }
    return {};
}

std::string FileTreeCreator::create(const File &file, const std::filesystem::path &path) const {
    const auto filePath = path / file.name;
    if (std::filesystem::exists(filePath)) {
        return "file exists at path '" + filePath.string() + "'";
    }
    std::ofstream outputFile(filePath);
    outputFile.write(file.content.data(), file.content.size());
    outputFile.close();
    return {};
}
