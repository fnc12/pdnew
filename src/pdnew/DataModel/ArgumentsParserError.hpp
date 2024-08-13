#pragma once

#include <string>

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
