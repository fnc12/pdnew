#pragma once

#include <filesystem>   //  std::filesystem::path
#include <string>   //  std::string
#include <initializer_list> //  std::initializer_list
#include <string_view>  //  std::string_view
#include <vector>   //  std::vector

#include "../DataModel/ProjectProgrammingLanguage.hpp"
#include "FileTreeCreator.hpp"

class ProjectCreator {
public:
    using ProgrammingLanguage = ProjectProgrammingLanguage;
    
    ProjectCreator();
    
    std::string createProject(ProgrammingLanguage programmingLanguage, 
                              std::filesystem::path directory, 
                              std::string_view projectName,
                              std::string_view bundleId,
                              std::string_view author) const;
    
    std::string makeCmakeListsContents(std::string_view projectName) const;
    std::string makePdxinfoContents(std::string_view bundleId, 
                                    std::string_view projectName,
                                    std::string_view author) const;
    std::string substitute(std::string sourceString, 
                           std::string_view tokenToReplace,
                           std::string_view replaceWith) const;
    std::string byteVectorToString(const std::vector<unsigned char> &vector) const;
    
    static const std::string_view cmakeListsContents;
    static const std::string_view pdxinfoContents;
    static const std::vector<unsigned char> wrappingContentPng;
    static const std::vector<unsigned char> iconPng;
    static const std::vector<unsigned char> iconPressedPng;
    static const std::vector<unsigned char> cardPng;
    static const std::vector<unsigned char> cardPressedPng;
    static const std::string_view mainCContents;
    static const std::string_view gitignoreContents;
    static const std::string_view mainLuaContents;
    
private:
    FileTreeCreator fileTreeCreator;
};
