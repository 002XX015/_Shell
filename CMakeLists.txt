cmake_minimum_required(VERSION 3.2)

project(SimplisticShell VERSION 0.1)

add_library(shellLib shell.cpp shell.hpp)
add_executable(exec main.cpp)
target_link_libraries(exec shellLib)
