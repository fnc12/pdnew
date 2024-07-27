#include "ProjectProgrammingLanguage.hpp"

std::array<ProjectProgrammingLanguage, 2> AllProjectProgrammingLanguages {
    ProjectProgrammingLanguage::c,
    ProjectProgrammingLanguage::lua,
};

std::string_view ProjectProgrammingLanguageToString(ProjectProgrammingLanguage projectProgrammingLanguage) {
    switch (projectProgrammingLanguage) {
        case ProjectProgrammingLanguage::c:
            return "c";
        case ProjectProgrammingLanguage::lua:
            return "lua";
    }
    return {};
}

std::optional<ProjectProgrammingLanguage> ProjectProgrammingLanguageFromString(std::string_view stringView) {
    for (const auto projectProgrammingLanguage : AllProjectProgrammingLanguages) {
        if (stringView == ProjectProgrammingLanguageToString(projectProgrammingLanguage)) {
            return projectProgrammingLanguage;
        }
    }
    return std::nullopt;
}
