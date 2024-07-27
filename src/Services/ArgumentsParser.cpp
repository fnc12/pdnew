#include "ArgumentsParser.hpp"
#include "../DataModel/ArgumentOption.hpp"

#include <string_view>  //  std::string_view
#include <vector>   //  std::vector
#include <algorithm>    //  std::find_if

ArgumentsParser::ArgumentsParser() = default;

std::variant<ArgumentsConfiguration, std::string> ArgumentsParser::parse(int argc, const char * argv[]) const {
    if (argc < 2) {
        return std::string("missing project name after ") + argv[0];
    }
    int argumentsParsedCount = 2;
    ArgumentsConfiguration argumentsConfiguration{std::string(argv[1])};
    std::vector<ArgumentOption> unusedArgumentOptions(AllArgumentOptions.begin(), AllArgumentOptions.end());
    while (argc > argumentsParsedCount) {
        if (unusedArgumentOptions.empty()) {
            return std::string("extra tokens found starting with '") + argv[argumentsParsedCount] + "'";
        }
        const std::string_view key = argv[argumentsParsedCount];
        auto argumentOptionMaybe = ArgumentOptionForString(key);
        if (!argumentOptionMaybe.has_value()) {
            std::string allKeysString;
            for (int argumentOptionIndex = 0; argumentOptionIndex < int(AllArgumentOptions.size()); ++argumentOptionIndex) {
                const auto argumentOption = AllArgumentOptions.at(argumentOptionIndex);
                const auto argumentOptionStringRepresentation = ArgumentOptionStringRepresentationFor(argumentOption);
                allKeysString += argumentOptionStringRepresentation.shortVersion;
                allKeysString += "|";
                allKeysString += argumentOptionStringRepresentation.longVersion;
                if (argumentOptionIndex < int(AllArgumentOptions.size() - 1)) {
                    allKeysString += "|";
                }
            }
            return std::string("incorrect key '") + key.data() + "'. Expected keys: " + allKeysString;
        }
        const auto argumentOption = argumentOptionMaybe.value();
        auto end = unusedArgumentOptions.end();
        auto unusedArgumentOptionsIt = std::find(unusedArgumentOptions.begin(), end, argumentOption);
        const auto keyIsUnused = unusedArgumentOptionsIt != end;
        if (!keyIsUnused) {
            return std::string("key is specified more than once");
        }
        unusedArgumentOptions.erase(unusedArgumentOptionsIt);
        unusedArgumentOptionsIt = end;
        ++argumentsParsedCount;
        if (argc <= argumentsParsedCount) {
            return std::string("value expected after key ") + key.data();
        }
        const std::string_view value = argv[argumentsParsedCount];
        switch (argumentOption) {
            case ArgumentOption::language: {
                const auto programmingLanguageMaybe = ProjectProgrammingLanguageFromString(value);
                if (!programmingLanguageMaybe.has_value()) {
                    std::string allValuesString;
                    for (int programmingLanguageIndex = 0; programmingLanguageIndex < int(AllProjectProgrammingLanguages.size()); ++programmingLanguageIndex) {
                        const auto programmingLanguage = AllProjectProgrammingLanguages.at(programmingLanguageIndex);
                        const auto programmingLanguageString = ProjectProgrammingLanguageToString(programmingLanguage);
                        allValuesString += programmingLanguageString;
                        if (programmingLanguageIndex < int(AllProjectProgrammingLanguages.size() - 1)) {
                            allValuesString += "|";
                        }
                    }
                    return std::string("incorrect language string '") + value.data() + "'. Expected values: " + allValuesString;
                }
                const auto programmingLanguage = programmingLanguageMaybe.value();
                argumentsConfiguration.projectProgrammingLanguage = programmingLanguage;
            } break;
            case ArgumentOption::directory: {
                argumentsConfiguration.projectDirectory = std::filesystem::path(value);
            } break;
            case ArgumentOption::bundleId:{
                argumentsConfiguration.projectBundleId = std::string(value);
            } break;
            case ArgumentOption::author: {
                argumentsConfiguration.projectAuthor = std::string(value);
            } break;
        }
        ++argumentsParsedCount;
    }
    return argumentsConfiguration;
}
