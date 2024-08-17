#include <catch2/catch_all.hpp>
#include <Services/ArgumentsParser.hpp>
#include <algorithm>    //  std::transform

TEST_CASE("ArgumentsParser", "[parse]") {
    struct TestCase {
        std::vector<std::string> arguments;
        ArgumentsParseResult expected;
    };
    const std::vector<TestCase> testCases = {
        
        //  success test cases
        {{"pdnew", "MyGame", "-l", "c", "-a", "fnc12"}, ArgumentsConfiguration{
            "MyGame", ProjectProgrammingLanguage::c, std::nullopt, std::nullopt, "fnc12",
        }},
        {{"pdnew", "MyGame", "--language", "c", "--author", "fnc12"}, ArgumentsConfiguration{
            "MyGame", ProjectProgrammingLanguage::c, std::nullopt, std::nullopt, "fnc12",
        }},
        {{"pdnew", "SuperBorat", "-l", "lua", "-a", "Somebody", "-d", "projects"}, ArgumentsConfiguration{
            "SuperBorat", ProjectProgrammingLanguage::lua, std::filesystem::path("projects"), std::nullopt, "Somebody",
        }},
        {{"pdnew", "SuperBorat", "--language", "lua", "--author", "Somebody", "--directory", "projects"}, ArgumentsConfiguration{
            "SuperBorat", ProjectProgrammingLanguage::lua, std::filesystem::path("projects"), std::nullopt, "Somebody",
        }},
        {{"pdnew", "JumpingGoat", "-l", "c", "-a", "Dua Lipa", "-d", "my_fancy_projects", "-b", "com.dualipa.jumpinggoat"},
            ArgumentsConfiguration{
                "JumpingGoat", ProjectProgrammingLanguage::c, std::filesystem::path("my_fancy_projects"), "com.dualipa.jumpinggoat", "Dua Lipa",
            }
        },
        {{"pdnew", "GTA10", "-a", "Akon"}, ArgumentsConfiguration{
            "GTA10", std::nullopt, std::nullopt, std::nullopt, "Akon",
        }},
        {{"pdnew", "RDR25"}, ArgumentsConfiguration{
            "RDR25", std::nullopt, std::nullopt, std::nullopt, std::nullopt,
        }},
        
        //  failure test cases
        {{"pdnew"}, ArgumentsParserError::makeMissingProjectName("pdnew")},
        {{"pdnew", "my_game", "-z"}, ArgumentsParserError::makeIncorrectKey("-z")},
        {{"pdnew", "MyGame", "-z", "c"}, ArgumentsParserError::makeIncorrectKey("-z")},
        {{"pdnew", "MyGame", "-l"}, ArgumentsParserError::makeValueExpectedAfterKey("-l")},
        {{"pdnew", "MyGame", "--language"}, ArgumentsParserError::makeValueExpectedAfterKey("--language")},
        {{"pdnew", "MyGame", "-b"}, ArgumentsParserError::makeValueExpectedAfterKey("-b")},
        {{"pdnew", "MyGame", "--bundleId"}, ArgumentsParserError::makeValueExpectedAfterKey("--bundleId")},
        {{"pdnew", "MyGame", "-d"}, ArgumentsParserError::makeValueExpectedAfterKey("-d")},
        {{"pdnew", "MyGame", "--directory"}, ArgumentsParserError::makeValueExpectedAfterKey("--directory")},
        {{"pdnew", "MyGame", "-a"}, ArgumentsParserError::makeValueExpectedAfterKey("-a")},
        {{"pdnew", "MyGame", "--author"}, ArgumentsParserError::makeValueExpectedAfterKey("--author")},
        {{"pdnew", "MyGame", "-l", "c", "-a", "PDiddy", "-b", "com.example.mygame", "-d", "projects", "something"}, ArgumentsParserError::makeExtraTokensFoundStarting("something")},
        {{"pdnew", "MyGame", "-l", "c", "-l"}, ArgumentsParserError::makeKeyIsSpecifiedMoreThanOnce("-l")},
        {{"pdnew", "MyGame", "-l", "swift"}, ArgumentsParserError::makeIncorrectLanguageString("swift")},
    };
    for (auto &testCase : testCases) {
        ArgumentsParser argumentsParser;
        const auto arguments = [&testCase] {
            std::vector<std::string_view> arguments;
            const auto argumentsSize = int(testCase.arguments.size());
            arguments.reserve(argumentsSize);
            for (auto i = 0; i < argumentsSize; ++i) {
                arguments.push_back(testCase.arguments.at(i));
            }
            return arguments;
        }();
        const auto result = argumentsParser.parse(arguments);
        REQUIRE(result == testCase.expected);
    }
}
