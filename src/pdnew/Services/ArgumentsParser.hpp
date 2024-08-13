#pragma once

#include <variant>  //  std::variant

#include "DataModel/ArgumentsConfiguration.hpp"
#include "DataModel/ArgumentsParserError.hpp"

class ArgumentsParser {
public:
    ArgumentsParser();
    
    std::variant<ArgumentsConfiguration, ArgumentsParserError> parse(int argc, const char * argv[]) const;
};
