#pragma once

#include <variant>  //  std::variant
#include <ostream>  //  std::ostream

#include "DataModel/ArgumentsConfiguration.hpp"
#include "DataModel/ArgumentsParserError.hpp"

class ArgumentsParseResult {
public:
    ArgumentsParseResult(ArgumentsConfiguration argumentsConfiguration);
    ArgumentsParseResult(ArgumentsParserError argumentsParserError);
    
    const ArgumentsParserError* error() const;
    ArgumentsConfiguration* success();
    
private:
    using Data = std::variant<ArgumentsConfiguration, ArgumentsParserError>;
    
    friend bool operator==(const ArgumentsParseResult &lhs, const ArgumentsParseResult &rhs);
    friend std::ostream& operator<<(std::ostream &os, const ArgumentsParseResult &argumentsParseResult);
    
    Data data;
};

bool operator==(const ArgumentsParseResult &lhs, const ArgumentsParseResult &rhs);
std::ostream& operator<<(std::ostream &os, const ArgumentsParseResult &argumentsParseResult);
