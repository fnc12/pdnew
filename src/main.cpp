#include <iostream>
#include <filesystem>

#include "Services/ArgumentsParser.hpp"
#include "Services/ProjectCreator.hpp"
#include "Misc.hpp"

using std::cout;
using std::cin;
using std::cerr;
using std::endl;

void printUsage();

#include <fstream>

int main(int argc, const char * argv[]) {
    /*{
        std::ifstream file("/Users/yevgeniyzakharov/Desktop/playdate/qumalak/Source/titles/card-pressed.png");
        cout << std::hex;
        int counter = 0;
        while (!file.eof()) {
            unsigned char c;
            file.read((char*)&c, 1);
            cout << "0x" << unsigned(c) << ", ";
            ++counter;
            if (counter % 16 == 0) {
                cout << endl;
            }
        }
        cout << endl;
        return 2;
    }*/
    
    ArgumentsParser argumentsParser;
    auto parseResult = argumentsParser.parse(argc, argv);
    if (std::holds_alternative<std::string>(parseResult)) {
        const auto errorText = std::get<std::string>(parseResult);
        cerr << errorText << endl;
        printUsage();
        return 1;
    }
    auto &argumentsConfiguration = std::get<ArgumentsConfiguration>(parseResult);
    if (!argumentsConfiguration.projectProgrammingLanguage.has_value()) {
        argumentsConfiguration.projectProgrammingLanguage = ProjectProgrammingLanguage::lua;
    }
    if (!argumentsConfiguration.projectDirectory.has_value()) {
        argumentsConfiguration.projectDirectory = std::filesystem::current_path();
    }
    const auto projectNameWithoutSpaces = removeAllSpaces(argumentsConfiguration.projectName);
    if (!argumentsConfiguration.projectBundleId.has_value()) {
        std::string projectBundleId;
        const auto defaultBundleId = "com.example." + projectNameWithoutSpaces;
        cout << "Input project bundle id or press Enter to leave default value " << defaultBundleId << endl;
        cin >> projectBundleId;
        if (projectBundleId.empty()) {
            argumentsConfiguration.projectBundleId = std::move(projectBundleId);
            cout << "Ok, default bundle ID '" << defaultBundleId << "' will be used." << endl;
        } else {
            argumentsConfiguration.projectBundleId = defaultBundleId;
        }
    }
    if (!argumentsConfiguration.projectAuthor.has_value()) {
        std::string projectAuthor;
        cout << "Input project author:" << endl;
        cin >> projectAuthor;
        argumentsConfiguration.projectAuthor = std::move(projectAuthor);
    }
    
    ProjectCreator projectCreator;
    auto errorText = projectCreator.createProject(argumentsConfiguration.projectProgrammingLanguage.value(),
                                                  argumentsConfiguration.projectDirectory.value(),
                                                  argumentsConfiguration.projectName,
                                                  projectNameWithoutSpaces,
                                                  argumentsConfiguration.projectBundleId.value(),
                                                  argumentsConfiguration.projectAuthor.value());
    if (!errorText.empty()) {
        cerr << errorText << endl;
        return 1;
    }
    return 0;
}

void printUsage() {
    cout << "pdnew {project-name} -l|--language c|lua -a|--author {author-name} [-d|--directory {parent-folder-path}] [-b|--bundleId {bundleId}]" << endl;
}
