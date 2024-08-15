#pragma once

#include <string>   //  std::string
#include <ostream>  //  std::ostream

#include "DataModel/ArgumentOption.hpp"

class ArgumentsParserError {
public:
    struct MissingProjectName {
        std::string after;
        
        std::string what() const;
    };
    
    struct ExtraTokensFoundStarting {
        std::string with;
        
        std::string what() const;
    };
    
    struct IncorrectKey {
        std::string key;
        
        std::string what() const;
    };
    
    struct KeyIsSpecifiedMoreThanOnce {
        std::string key;
        
        std::string what() const;
    };
    
    struct ValueExpectedAfterKey {
        std::string key;
        
        std::string what() const;
    };
    
    struct IncorrectLanguageString {
        std::string value;
        
        std::string what() const;
    };
    
    using Data = std::variant<
    MissingProjectName,
    ExtraTokensFoundStarting,
    IncorrectKey,
    KeyIsSpecifiedMoreThanOnce,
    ValueExpectedAfterKey,
    IncorrectLanguageString>;
    
    Data data;
    
    std::string what() const;
    
    static ArgumentsParserError makeIncorrectLanguageString(std::string value);
    
    static ArgumentsParserError makeValueExpectedAfterKey(std::string key);
    
    static ArgumentsParserError makeKeyIsSpecifiedMoreThanOnce(std::string key);
    
    static ArgumentsParserError makeIncorrectKey(std::string key);
    
    static ArgumentsParserError makeExtraTokensFoundStarting(std::string with);
    
    static ArgumentsParserError makeMissingProjectName(std::string after);
};

std::ostream& operator<<(std::ostream &os, const ArgumentsParserError &argumentsParserError);
std::ostream& operator<<(std::ostream &os, const ArgumentsParserError::MissingProjectName &missingProjectName);
std::ostream& operator<<(std::ostream &os, const ArgumentsParserError::ExtraTokensFoundStarting &extraTokensFoundStarting);
std::ostream& operator<<(std::ostream &os, const ArgumentsParserError::IncorrectKey &incorrectKey);
std::ostream& operator<<(std::ostream &os, const ArgumentsParserError::KeyIsSpecifiedMoreThanOnce &keyIsSpecifiedMoreThanOnce);
std::ostream& operator<<(std::ostream &os, const ArgumentsParserError::ValueExpectedAfterKey &valueExpectedAfterKey);
std::ostream& operator<<(std::ostream &os, const ArgumentsParserError::IncorrectLanguageString &incorrectLanguageString);

bool operator==(const ArgumentsParserError &lhs, const ArgumentsParserError &rhs);
bool operator==(const ArgumentsParserError::MissingProjectName& lhs, const ArgumentsParserError::MissingProjectName& rhs);
bool operator==(const ArgumentsParserError::ExtraTokensFoundStarting& lhs, const ArgumentsParserError::ExtraTokensFoundStarting& rhs);
bool operator==(const ArgumentsParserError::IncorrectKey& lhs, const ArgumentsParserError::IncorrectKey& rhs);
bool operator==(const ArgumentsParserError::KeyIsSpecifiedMoreThanOnce& lhs, const ArgumentsParserError::KeyIsSpecifiedMoreThanOnce& rhs);
bool operator==(const ArgumentsParserError::ValueExpectedAfterKey& lhs, const ArgumentsParserError::ValueExpectedAfterKey& rhs);
bool operator==(const ArgumentsParserError::IncorrectLanguageString& lhs, const ArgumentsParserError::IncorrectLanguageString& rhs);
