#pragma once

#include <string_view>  //  std::string_view

class ArgumentOptionStringRepresentation {
public:
    std::string_view shortVersion;
    std::string_view longVersion;
    
    bool operator==(std::string_view stringView) const;
};
