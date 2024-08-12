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

constexpr std::array<ArgumentOption, 4> AllArgumentOptions{
    ArgumentOption::language,
    ArgumentOption::directory,
    ArgumentOption::bundleId,
    ArgumentOption::author,
};

ArgumentOptionStringRepresentation ArgumentOptionStringRepresentationFor(ArgumentOption argumentOption);
std::optional<ArgumentOption> ArgumentOptionForString(std::string_view stringView);
