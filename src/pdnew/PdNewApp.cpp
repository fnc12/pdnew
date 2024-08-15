#include "PdNewApp.hpp"
#include "Services/ArgumentsParser.hpp"
#include "Misc.hpp"

#include <iostream>

using std::cout;
using std::cin;
using std::cerr;
using std::endl;

PdNewApp::PdNewApp(const UsagePrinter &usagePrinter, const ProjectCreator &projectCreator):
usagePrinter(usagePrinter),
projectCreator(projectCreator)
{}

int PdNewApp::work(const std::vector<std::string_view> &arguments) {
    ArgumentsParser argumentsParser;
    auto parseResult = argumentsParser.parse(arguments);
    if (auto *error = parseResult.error()) {
        const auto errorText = error->what();
        cerr << errorText << endl;
        usagePrinter.printUsage();
        return 1;
    }
//    auto &argumentsConfiguration = std::get<ArgumentsConfiguration>(parseResult);
    auto &argumentsConfiguration = *parseResult.success();
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
