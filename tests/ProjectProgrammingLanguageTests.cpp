#include <catch2/catch_all.hpp>
#include <DataModel/ProjectProgrammingLanguage.hpp>

TEST_CASE("ProjectProgrammingLanguage", "[AllProjectProgrammingLanguages]") {
    STATIC_REQUIRE(AllProjectProgrammingLanguages.size() == 2);
    STATIC_REQUIRE(AllProjectProgrammingLanguages.at(0) == ProjectProgrammingLanguage::c);
    STATIC_REQUIRE(AllProjectProgrammingLanguages.at(1) == ProjectProgrammingLanguage::lua);
}

TEST_CASE("ProjectProgrammingLanguage", "[ProjectProgrammingLanguageToString]") {
    struct TestCase {
        ProjectProgrammingLanguage argument;
        std::string_view expected;
    };
    const std::vector<TestCase> testCases = {
        {ProjectProgrammingLanguage::c, "c"},
        {ProjectProgrammingLanguage::lua, "lua"},
    };
    for (auto &testCase : testCases) {
        const auto result = ProjectProgrammingLanguageToString(testCase.argument);
        REQUIRE(result == testCase.expected);
    }
}

TEST_CASE("ProjectProgrammingLanguage", "[ProjectProgrammingLanguageFromString]") {
    struct TestCase {
        std::string_view argument;
        std::optional<ProjectProgrammingLanguage> expected;
    };
    const std::vector<TestCase> testCases = {
        {"c", ProjectProgrammingLanguage::c},
        {"lua", ProjectProgrammingLanguage::lua},
        {"swift", std::nullopt},
        {"cpp", std::nullopt},
    };
    for (auto &testCase : testCases) {
        const auto result = ProjectProgrammingLanguageFromString(testCase.argument);
        REQUIRE(result == testCase.expected);
    }
}
