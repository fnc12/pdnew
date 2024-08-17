#include "ProjectCreator.hpp"

#include <algorithm>    //  std::copy

#include "../Misc.hpp"

ProjectCreator::ProjectCreator(const FileTreeCreator &fileTreeCreator):
fileTreeCreator(fileTreeCreator)
{}

std::string ProjectCreator::createProject(ProgrammingLanguage programmingLanguage, 
                                          std::filesystem::path directory,
                                          std::string_view projectName,
                                          std::string_view projectNameWithoutSpaces,
                                          std::string_view bundleId,
                                          std::string_view author) const
{
    if (!std::filesystem::exists(directory)) {
        return std::string("parent directory does not exist at path '") + directory.string() + "'";
    }
    
    switch (programmingLanguage) {
        case ProjectProgrammingLanguage::c: {
            const Folder projectStructure{std::string(projectName), {
                File{".gitignore", std::string(this->gitignoreContents)},
                File{"CMakeLists.txt", this->makeCmakeListsContents(projectNameWithoutSpaces)},
                Folder{"Source", {
                    Folder{"images", {}},
                    Folder{"music", {}},
                    Folder{"sounds", {}},
                    Folder{"titles", {
                        File{"wrapping-pattern.png", this->byteVectorToString(this->wrappingContentPng)},
                        File{"icon.png", this->byteVectorToString(this->iconPng)},
                        File{"icon-pressed.png", this->byteVectorToString(this->iconPressedPng)},
                        File{"card.png", this->byteVectorToString(this->cardPng)},
                        File{"card-pressed.png", this->byteVectorToString(this->cardPressedPng)},
                        Folder{"card-highlighted", {}},
                    }},
                    File{"main.lua", ""},
                    File{"pdxinfo", this->makePdxinfoContents(bundleId, projectName, author)}
                }},
                Folder{"src", {
                    File{"main.c", std::string(this->mainCContents)},
                }},
            }};
            return this->fileTreeCreator.create(projectStructure, directory);
        } break;
        case ProjectProgrammingLanguage::lua: {
            const Folder projectStructure{std::string(projectName), {
                File{".gitignore", "*.pdx"},
                Folder{"Source", {
                    File{"main.lua", std::string(this->mainLuaContents)},
                    File{"pdxinfo", this->makePdxinfoContents(bundleId, projectName, author)}
                }},
            }};
            return this->fileTreeCreator.create(projectStructure, directory);
        } break;
    }
    
    return {};
}

std::string ProjectCreator::makeCmakeListsContents(std::string_view projectName) const {
    return this->substitute(std::string(cmakeListsContents), "{{project-name}}", projectName);
}

std::string ProjectCreator::makePdxinfoContents(std::string_view bundleId,
                                                std::string_view projectName,
                                                std::string_view author) const
{
    auto resultWithBundleId = this->substitute(std::string(pdxinfoContents), "{{bundle-id}}", bundleId);
    auto resultWithName = this->substitute(std::move(resultWithBundleId), "{{project-name}}", projectName);
    auto resultWithAuthor = this->substitute(std::move(resultWithName), "{{author}}", author);
//    auto resultWithDescription = this->substitute(std::move(resultWithAuthor), "{{description}}", description);
    return resultWithAuthor;
}

std::string ProjectCreator::substitute(std::string result,
                                       std::string_view tokenToReplace,
                                       std::string_view replaceWith) const
{
    while (true) {
        auto startIndex = result.find(tokenToReplace);
        if (startIndex == result.npos) {
            break;
        }
        result.replace(startIndex, tokenToReplace.length(), replaceWith);
    }
    return result;
}

std::string ProjectCreator::byteVectorToString(const std::vector<unsigned char> &vector) const {
    std::string result;
    result.reserve(vector.size());
    std::copy(vector.begin(), vector.end(), std::back_inserter(result));
    return result;
}
