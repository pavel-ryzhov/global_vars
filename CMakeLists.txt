cmake_minimum_required(VERSION 3.28)
project(global_vars)

set(CMAKE_CXX_STANDARD 20)

find_package(LLVM REQUIRED CONFIG)
find_package(Clang REQUIRED CONFIG)

include_directories(${LLVM_INCLUDE_DIRS})
include_directories(${CLANG_INCLUDE_DIRS})
add_definitions(${LLVM_DEFINITIONS})

add_executable(global_vars main.cpp)

target_link_libraries(global_vars
        clangTooling
        clangBasic
        clangASTMatchers
)

