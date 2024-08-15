#pragma once

#include <string_view>  //  std::string_view
#include <vector>   //  std::vector

#include "Services/UsagePrinter.hpp"
#include "Services/ProjectCreator.hpp"

class PdNewApp {
public:
    PdNewApp(const UsagePrinter &usagePrinter, const ProjectCreator &projectCreator);
    
    int work(const std::vector<std::string_view> &arguments);
    
private:
    const UsagePrinter &usagePrinter;
    const ProjectCreator &projectCreator;
};
