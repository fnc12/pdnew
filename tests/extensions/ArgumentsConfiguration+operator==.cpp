#include "ArgumentsConfiguration+operator==.hpp"

bool operator==(const ArgumentsConfiguration& lhs, const ArgumentsConfiguration& rhs) {
    return lhs.projectName == rhs.projectName &&
           lhs.projectProgrammingLanguage == rhs.projectProgrammingLanguage &&
           lhs.projectDirectory == rhs.projectDirectory &&
           lhs.projectBundleId == rhs.projectBundleId &&
           lhs.projectAuthor == rhs.projectAuthor;
}
