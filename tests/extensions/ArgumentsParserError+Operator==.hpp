#pragma once

#include <DataModel/ArgumentsParserError.hpp>

bool operator==(const ArgumentsParserError &lhs, const ArgumentsParserError &rhs);
bool operator==(const ArgumentsParserError::MissingProjectName& lhs, const ArgumentsParserError::MissingProjectName& rhs);
bool operator==(const ArgumentsParserError::ExtraTokensFoundStarting& lhs, const ArgumentsParserError::ExtraTokensFoundStarting& rhs);
bool operator==(const ArgumentsParserError::IncorrectKey& lhs, const ArgumentsParserError::IncorrectKey& rhs);
bool operator==(const ArgumentsParserError::KeyIsSpecifiedMoreThanOnce& lhs, const ArgumentsParserError::KeyIsSpecifiedMoreThanOnce& rhs);
bool operator==(const ArgumentsParserError::ValueExpectedAfterKey& lhs, const ArgumentsParserError::ValueExpectedAfterKey& rhs);
bool operator==(const ArgumentsParserError::IncorrectLanguageString& lhs, const ArgumentsParserError::IncorrectLanguageString& rhs);
