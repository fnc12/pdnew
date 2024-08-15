#include "ArgumentsParseResult.hpp"

ArgumentsParseResult::ArgumentsParseResult(ArgumentsConfiguration argumentsConfiguration):
data(std::move(argumentsConfiguration))
{}

ArgumentsParseResult::ArgumentsParseResult(ArgumentsParserError argumentsParserError):
data(std::move(argumentsParserError))
{}

const ArgumentsParserError* ArgumentsParseResult::error() const {
    if (std::holds_alternative<ArgumentsParserError>(this->data)) {
        return &std::get<ArgumentsParserError>(this->data);
    }
    return nullptr;
}

ArgumentsConfiguration* ArgumentsParseResult::success() {
    if (std::holds_alternative<ArgumentsConfiguration>(this->data)) {
        return &std::get<ArgumentsConfiguration>(this->data);
    }
    return nullptr;
}

bool operator==(const ArgumentsParseResult &lhs, const ArgumentsParseResult &rhs) {
    return std::visit([](const auto& l, const auto& r) {
        return l == r;
    }, lhs.data, rhs.data);
}

std::ostream& operator<<(std::ostream &os, const ArgumentsParseResult &argumentsParseResult) {
    std::visit([&os] (auto &value) {
        os << value;
    }, argumentsParseResult.data);
    return os;
}
