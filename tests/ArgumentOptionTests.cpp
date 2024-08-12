#include <catch2/catch_all.hpp>
#include <DataModel/ArgumentOption.hpp>

#include "ArgumentOptionStringRepresentation+operator==.hpp"

TEST_CASE("ArgumentOption", "[AllArgumentOptions]") {
    STATIC_REQUIRE(AllArgumentOptions.size() == 4);
    STATIC_REQUIRE(AllArgumentOptions.at(0) == ArgumentOption::language);
    STATIC_REQUIRE(AllArgumentOptions.at(1) == ArgumentOption::directory);
    STATIC_REQUIRE(AllArgumentOptions.at(2) == ArgumentOption::bundleId);
    STATIC_REQUIRE(AllArgumentOptions.at(3) == ArgumentOption::author);
}

TEST_CASE("ArgumentOption", "[ArgumentOptionStringRepresentationFor]") {
    struct TestCase {
        ArgumentOption argument;
        ArgumentOptionStringRepresentation expected;
    };
    const std::vector<TestCase> testCases = {
        {ArgumentOption::language, {"-l", "--language"}},
        {ArgumentOption::directory, {"-d", "--directory"}},
        {ArgumentOption::bundleId, {"-b", "--bundleId"}},
        {ArgumentOption::author, {"-a", "--author"}},
    };
    for (auto &testCase : testCases) {
        const auto result = ArgumentOptionStringRepresentationFor(testCase.argument);
        REQUIRE(result == testCase.expected);
    }
}

TEST_CASE("ArgumentOption", "[ArgumentOptionForString]") {
    struct TestCase {
        std::string_view argument;
        std::optional<ArgumentOption> expected;
    };
    const std::vector<TestCase> testCases = {
        {"-l", ArgumentOption::language},
        {"--language", ArgumentOption::language},
        {"-d", ArgumentOption::directory},
        {"--directory", ArgumentOption::directory},
        {"-b", ArgumentOption::bundleId},
        {"--bundleId", ArgumentOption::bundleId},
        {"-a", ArgumentOption::author},
        {"--author", ArgumentOption::author},
        {"-c", std::nullopt},
        {"--cyan", std::nullopt},
        {"-z", std::nullopt},
        {"--zaibatsu", std::nullopt},
    };
    for (auto &testCase : testCases) {
        const auto result = ArgumentOptionForString(testCase.argument);
        REQUIRE(result == testCase.expected);
    }
}
