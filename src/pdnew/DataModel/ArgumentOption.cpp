#include "ArgumentOption.hpp"

const std::array<ArgumentOption, 4> AllArgumentOptions {
    ArgumentOption::language,
    ArgumentOption::directory,
    ArgumentOption::bundleId,
    ArgumentOption::author,
};

ArgumentOptionStringRepresentation ArgumentOptionStringRepresentationFor(ArgumentOption argumentOption) {
    switch (argumentOption) {
        case ArgumentOption::language:
            return {"-l", "--language"};
        case ArgumentOption::directory:
            return {"-d", "--directory"};
        case ArgumentOption::bundleId:
            return {"-b", "--bundleId"};
        case ArgumentOption::author:
            return {"-a", "--author"};
    }
    return {};
}

std::optional<ArgumentOption> ArgumentOptionForString(std::string_view stringView) {
    for (const auto argumentOption : AllArgumentOptions) {
        const auto stringRepresentation = ArgumentOptionStringRepresentationFor(argumentOption);
        if (stringRepresentation == stringView) {
            return argumentOption;
        }
    }
    return std::nullopt;
}
