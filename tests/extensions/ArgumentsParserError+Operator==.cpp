#include "ArgumentsParserError+Operator==.hpp"

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
