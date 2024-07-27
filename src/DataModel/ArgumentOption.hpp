#pragma once

#include <optional> //  std::optional, std::nullopt
#include <string_view>  //  std::string_view
#include <array>    //  std::array

#include "ArgumentOptionStringRepresentation.hpp"

enum class ArgumentOption {
    language,
    directory,
    bundleId,
    author,
};

extern const std::array<ArgumentOption, 4> AllArgumentOptions;

ArgumentOptionStringRepresentation ArgumentOptionStringRepresentationFor(ArgumentOption argumentOption);
std::optional<ArgumentOption> ArgumentOptionForString(std::string_view stringView);
