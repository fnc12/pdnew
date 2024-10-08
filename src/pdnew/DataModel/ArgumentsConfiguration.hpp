#pragma once

#include <string>   //  std::string
#include <optional> //  std::optional
#include <filesystem>   //  std::filesystem::path

#include "ProjectProgrammingLanguage.hpp"

class ArgumentsConfiguration {
public:    
    std::string projectName;
    std::optional<ProjectProgrammingLanguage> projectProgrammingLanguage;
    std::optional<std::filesystem::path> projectDirectory;
    std::optional<std::string> projectBundleId;
    std::optional<std::string> projectAuthor;
};

bool operator==(const ArgumentsConfiguration& lhs, const ArgumentsConfiguration& rhs);
