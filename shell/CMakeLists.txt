cmake_minimum_required(VERSION 3.2)

project(Shell)

add_library(shell shell.cpp shell.hpp)
add_executable(start main.cpp)

target_link_libraries(start shell)
