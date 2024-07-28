#include "Misc.hpp"

#include <algorithm>

std::string removeAllSpaces(std::string_view stringView) {
    std::string result(stringView);
    result.erase(std::remove(result.begin(), result.end(), ' '), result.end());
    return result;
}
