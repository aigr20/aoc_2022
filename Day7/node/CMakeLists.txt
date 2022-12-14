add_library(node node.cpp)
target_compile_options(node PRIVATE -Wall -Werror)
target_include_directories(node PRIVATE ".")
