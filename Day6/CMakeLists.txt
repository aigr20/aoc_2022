cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

project(Day6 VERSION 1.0)

add_executable(Day6 main.cpp)
target_compile_options(Day6 PRIVATE -Werror -Wall)
target_include_directories(Day6 PUBLIC
    "${PROJECT_BINARY_DIR}"
)
