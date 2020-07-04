cmake_minimum_required(VERSION 3.4.3)

project(flare)

set(CXX "clang++")
set(CMAKE_CXX_STANDARD 20)

set(CMAKE_CXX_FLAGS_DEBUG "-Wall -W -Werror -g -Wno-unused-parameter")
set(CMAKE_CXX_FLAGS "-O3 -Wall -W -pedantic")


find_package(LLVM REQUIRED CONFIG)
include_directories(${LLVM_INCLUDE_DIRS})
add_definitions(${LLVM_DEFINITIONS})
message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")
message(STATUS "Using C_FLAGS: ${CMAKE_CXX_FLAGS}")


add_subdirectory(src/)
