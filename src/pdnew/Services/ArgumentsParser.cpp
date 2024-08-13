#include "ArgumentsParser.hpp"

#include <string_view>  //  std::string_view
#include <vector>   //  std::vector
#include <algorithm>    //  std::find_if

ArgumentsParser::ArgumentsParser() = default;

std::variant<ArgumentsConfiguration, ArgumentsParserError> ArgumentsParser::parse(int argc, const char * argv[]) const {
    if (argc < 2) {
        return ArgumentsParserError::makeMissingProjectName(argv[0]);
    }
    int argumentsParsedCount = 2;
    ArgumentsConfiguration argumentsConfiguration{std::string(argv[1])};
    std::vector<ArgumentOption> unusedArgumentOptions(AllArgumentOptions.begin(), AllArgumentOptions.end());
    while (argc > argumentsParsedCount) {
        if (unusedArgumentOptions.empty()) {
            return ArgumentsParserError::makeExtraTokensFoundStarting(argv[argumentsParsedCount]);
        }
        const std::string_view key = argv[argumentsParsedCount];
        auto argumentOptionMaybe = ArgumentOptionForString(key);
        if (!argumentOptionMaybe.has_value()) {
            return ArgumentsParserError::makeIncorrectKey(std::string(key));
        }
        const auto argumentOption = argumentOptionMaybe.value();
        auto end = unusedArgumentOptions.end();
        auto unusedArgumentOptionsIt = std::find(unusedArgumentOptions.begin(), end, argumentOption);
        const auto keyIsUnused = unusedArgumentOptionsIt != end;
        if (!keyIsUnused) {
            return ArgumentsParserError::makeKeyIsSpecifiedMoreThanOnce(std::string(key));
        }
        unusedArgumentOptions.erase(unusedArgumentOptionsIt);
        unusedArgumentOptionsIt = end;
        ++argumentsParsedCount;
        if (argc <= argumentsParsedCount) {
            return ArgumentsParserError::makeValueExpectedAfterKey(std::string(key));
        }
        const std::string_view value = argv[argumentsParsedCount];
        switch (argumentOption) {
            case ArgumentOption::language: {
                const auto programmingLanguageMaybe = ProjectProgrammingLanguageFromString(value);
                if (!programmingLanguageMaybe.has_value()) {
                    return ArgumentsParserError::makeIncorrectLanguageString(std::string(value));
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
