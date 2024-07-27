#include "ArgumentOptionStringRepresentation.hpp"

bool ArgumentOptionStringRepresentation::operator==(std::string_view stringView) const {
    return this->shortVersion == stringView || this->longVersion == stringView;
}
