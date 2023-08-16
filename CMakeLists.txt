cmake_minimum_required(VERSION 3.10)
add_executable(Compiler main.c)
project(Compiler VERSION 1.0)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

#target_include_directories(Compiler PUBLIC
#                            "${PROJECT_BINARY_DIR}"
#                            )
