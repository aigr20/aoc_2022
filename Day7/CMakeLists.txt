cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

project(Day7 VERSION 1.0)

add_executable(Day7 main.cpp node/node.hpp)
target_include_directories(Day7 PUBLIC
    "${PROJECT_BINARY_DIR}"
    "${PROJECT_SOURCE_DIR}/node"
)
add_subdirectory(node)
target_link_libraries(Day7 PUBLIC node)
