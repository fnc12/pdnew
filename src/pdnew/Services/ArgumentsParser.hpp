#pragma once

#include <vector>   //  std::vector
#include <string_view>  //  std::string_view

#include "DataModel/ArgumentsParseResult.hpp"

class ArgumentsParser {
public:
    ArgumentsParser();
    
    ArgumentsParseResult parse(const std::vector<std::string_view> &arguments) const;
};
