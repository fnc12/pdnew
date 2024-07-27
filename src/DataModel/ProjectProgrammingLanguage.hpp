#pragma once

#include <array>    //  std::array
#include <string_view>  //  std::string_view
#include <optional> //  std::optional, std::nullopt

enum class ProjectProgrammingLanguage {
    c,
    lua,
};

extern std::array<ProjectProgrammingLanguage, 2> AllProjectProgrammingLanguages;

std::string_view ProjectProgrammingLanguageToString(ProjectProgrammingLanguage projectProgrammingLanguage);
std::optional<ProjectProgrammingLanguage> ProjectProgrammingLanguageFromString(std::string_view stringView);
