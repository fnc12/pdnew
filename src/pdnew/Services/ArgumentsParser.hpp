#pragma once

#include <variant>  //  std::variant
#include <vector>   //  std::vector
#include <string_view>  //  std::string_view

#include "DataModel/ArgumentsConfiguration.hpp"
#include "DataModel/ArgumentsParserError.hpp"

class ArgumentsParser {
public:
    ArgumentsParser();
    
    std::variant<ArgumentsConfiguration, ArgumentsParserError> parse(const std::vector<std::string_view> &arguments) const;
};
