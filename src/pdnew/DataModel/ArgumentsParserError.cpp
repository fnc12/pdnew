#include "ArgumentsParserError.hpp"
#include "DataModel/ProjectProgrammingLanguage.hpp"

std::string ArgumentsParserError::MissingProjectName::what() const {
    return "missing project name after " + this->after;
}

std::string ArgumentsParserError::ExtraTokensFoundStarting::what() const {
    return "extra tokens found starting with '" + this->with + "'";
}

std::string ArgumentsParserError::IncorrectKey::what() const {
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
    return "incorrect key '" + this->key + "'. Expected keys: " + allKeysString;
}

std::string ArgumentsParserError::KeyIsSpecifiedMoreThanOnce::what() const {
    return "key '" + this->key + "' is specified more than once";
}

std::string ArgumentsParserError::ValueExpectedAfterKey::what() const {
    return "value expected after key '" + this->key + "'";
}

std::string ArgumentsParserError::IncorrectLanguageString::what() const {
    std::string allValuesString;
    for (int programmingLanguageIndex = 0; programmingLanguageIndex < int(AllProjectProgrammingLanguages.size()); ++programmingLanguageIndex) {
        const auto programmingLanguage = AllProjectProgrammingLanguages.at(programmingLanguageIndex);
        const auto programmingLanguageString = ProjectProgrammingLanguageToString(programmingLanguage);
        allValuesString += programmingLanguageString;
        if (programmingLanguageIndex < int(AllProjectProgrammingLanguages.size() - 1)) {
            allValuesString += "|";
        }
    }
    return "incorrect language string '" + this->value + "'. Expected values: " + allValuesString;
}

std::string ArgumentsParserError::what() const {
    return std::visit([] (auto &value) {
        return value.what();
    }, this->data);
}

ArgumentsParserError ArgumentsParserError::makeIncorrectLanguageString(std::string value) {
    return {IncorrectLanguageString{std::move(value)}};
}

ArgumentsParserError ArgumentsParserError::makeValueExpectedAfterKey(std::string key) {
    return {ValueExpectedAfterKey{std::move(key)}};
}

ArgumentsParserError ArgumentsParserError::makeKeyIsSpecifiedMoreThanOnce(std::string key) {
    return {KeyIsSpecifiedMoreThanOnce{std::move(key)}};
}

ArgumentsParserError ArgumentsParserError::makeIncorrectKey(std::string key) {
    return {IncorrectKey{std::move(key)}};
}

ArgumentsParserError ArgumentsParserError::makeExtraTokensFoundStarting(std::string with) {
    return {ExtraTokensFoundStarting{std::move(with)}};
}

ArgumentsParserError ArgumentsParserError::makeMissingProjectName(std::string after) {
    return {MissingProjectName{std::move(after)}};
}

std::ostream& operator<<(std::ostream &os, const ArgumentsParserError &argumentsParserError) {
    return std::visit([&os] (auto &value) -> std::ostream& {
        return os << value;
    }, argumentsParserError.data);
}

std::ostream& operator<<(std::ostream &os, const ArgumentsParserError::MissingProjectName &missingProjectName) {
    return os << "MissingProjectName(" << missingProjectName.after << ")";
}

std::ostream& operator<<(std::ostream &os, const ArgumentsParserError::ExtraTokensFoundStarting &extraTokensFoundStarting) {
    return os << "ExtraTokensFoundStarting(" << extraTokensFoundStarting << ")";
}

std::ostream& operator<<(std::ostream &os, const ArgumentsParserError::IncorrectKey &incorrectKey) {
    return os << "IncorrectKey(" << incorrectKey.key << ")";
}

std::ostream& operator<<(std::ostream &os, const ArgumentsParserError::KeyIsSpecifiedMoreThanOnce &keyIsSpecifiedMoreThanOnce) {
    return os << "KeyIsSpecifiedMoreThanOnce(" << keyIsSpecifiedMoreThanOnce.key << ")";
}

std::ostream& operator<<(std::ostream &os, const ArgumentsParserError::ValueExpectedAfterKey &valueExpectedAfterKey) {
    return os << "ValueExpectedAfterKey(" << valueExpectedAfterKey.key << ")";
}

std::ostream& operator<<(std::ostream &os, const ArgumentsParserError::IncorrectLanguageString &incorrectLanguageString) {
    return os << "IncorrectLanguageString(" << incorrectLanguageString.value << ")";
}

bool operator==(const ArgumentsParserError &lhs, const ArgumentsParserError &rhs) {
    return lhs.data == rhs.data;
}

bool operator==(const ArgumentsParserError::MissingProjectName& lhs, const ArgumentsParserError::MissingProjectName& rhs) {
    return lhs.after == rhs.after;
}

bool operator==(const ArgumentsParserError::ExtraTokensFoundStarting& lhs, const ArgumentsParserError::ExtraTokensFoundStarting& rhs) {
    return lhs.with == rhs.with;
}

bool operator==(const ArgumentsParserError::IncorrectKey& lhs, const ArgumentsParserError::IncorrectKey& rhs) {
    return lhs.key == rhs.key;
}

bool operator==(const ArgumentsParserError::KeyIsSpecifiedMoreThanOnce& lhs, const ArgumentsParserError::KeyIsSpecifiedMoreThanOnce& rhs) {
    return lhs.key == rhs.key;
}

bool operator==(const ArgumentsParserError::ValueExpectedAfterKey& lhs, const ArgumentsParserError::ValueExpectedAfterKey& rhs) {
    return lhs.key == rhs.key;
}

bool operator==(const ArgumentsParserError::IncorrectLanguageString& lhs, const ArgumentsParserError::IncorrectLanguageString& rhs) {
    return lhs.value == rhs.value;
}
