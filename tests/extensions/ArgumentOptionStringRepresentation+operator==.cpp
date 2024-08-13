#include "ArgumentOptionStringRepresentation+operator==.hpp"

bool operator==(const ArgumentOptionStringRepresentation &lhs, const ArgumentOptionStringRepresentation &rhs) {
    return lhs.longVersion == rhs.longVersion && lhs.shortVersion == rhs.shortVersion;
}
