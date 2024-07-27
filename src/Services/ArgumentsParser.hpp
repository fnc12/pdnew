#pragma once

#include <variant>  //  std::variant

#include "../DataModel/ArgumentsConfiguration.hpp"

class ArgumentsParser {
public:
    ArgumentsParser();
    
    std::variant<ArgumentsConfiguration, std::string> parse(int argc, const char * argv[]) const;
};
