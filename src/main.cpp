#include <filesystem>

#include "PdNewApp.hpp"

int main(int argc, const char * argv[]) {
    
    //  convert arguments to vector of string views
    const auto arguments = [argc, argv] {
        std::vector<std::string_view> arguments;
        arguments.reserve(argc);
        for (auto i = 0; i < argc; ++i) {
            arguments.push_back(std::string_view(argv[i]));
        }
        return arguments;
    }();
    
    UsagePrinter usagePrinter;
    FileTreeCreator fileTreeCreator;
    ProjectCreator projectCreator(fileTreeCreator);
    PdNewApp pdNewApp(usagePrinter, projectCreator);
    return pdNewApp.work(arguments);
}
