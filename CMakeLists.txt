cmake_minimum_required(VERSION 3.8)
project(pdnew VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

# FIND_PACKAGE_ARGS is available since 3.24
if(CMAKE_VERSION VERSION_LESS 3.24)
    FetchContent_Declare(
        Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG v3.2.1
    )
else()
    FetchContent_Declare(
        Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG v3.2.1
        # prefer find_package() over building from source
        FIND_PACKAGE_ARGS 3 CONFIG
    )
endif()

FetchContent_MakeAvailable(Catch2)

file(GLOB LIB_SOURCE_FILES src/pdnew/*.cpp src/pdnew/*.hpp src/pdnew/*/*.cpp src/pdnew/*/*.hpp)

add_library(pdnew_lib STATIC ${LIB_SOURCE_FILES})
target_include_directories(pdnew_lib PUBLIC src/pdnew/)

file(GLOB TEST_FILES tests/*.cpp tests/*.hpp)

add_executable(pdnew src/main.cpp)
target_link_libraries(pdnew PRIVATE pdnew_lib)

add_executable(unit_tests ${TEST_FILES})
target_link_libraries(unit_tests PRIVATE pdnew_lib Catch2::Catch2WithMain)

install(TARGETS pdnew DESTINATION bin)
