cmake_minimum_required(VERSION 3.10)
project(example_fapolicyd_deny_shell)

set(CMAKE_CXX_STANDARD 14)

# lib
add_library(boo_lib SHARED lib.cpp)
set_target_properties(boo_lib PROPERTIES OUTPUT_NAME boo)

# main
add_executable(boo main.cpp)
target_link_libraries(boo boo_lib)
