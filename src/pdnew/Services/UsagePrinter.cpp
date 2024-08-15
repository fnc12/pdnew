#include "UsagePrinter.hpp"

#include <iostream>

using std::cout;
using std::endl;

UsagePrinter::UsagePrinter() = default;

void UsagePrinter::printUsage() const {
    cout << "pdnew {project-name} -l|--language c|lua -a|--author {author-name} [-d|--directory {parent-folder-path}] [-b|--bundleId {bundleId}]" << endl;
}
