cmake_minimum_required(VERSION 3.8)
project(pdnew VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB SOURCE_FILES src/*.cpp src/*.hpp src/*/*.cpp src/*/*.hpp)

add_executable(pdnew ${SOURCE_FILES})