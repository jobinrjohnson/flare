cmake_minimum_required(VERSION 3.4.3)

project(flare)

set(CXX "g++")
set(CMAKE_CXX_STANDARD 20)

set(CMAKE_CXX_FLAGS_DEBUG "-Wall -W -Werror -g -Wno-unused-parameter -Wno-redundant-move")
set(CMAKE_CXX_FLAGS "-O3 -Wall -W -pedantic -Wno-unused-parameter")

set(CMAKE_CXX_FLAGS_DEBUG "${true} -DFLARE_DEBUG")

# TODO add more platforms
if(APPLE)
    add_definitions(-DTARGET_DARWIN)
endif()


find_package(LLVM REQUIRED CONFIG)
include_directories(${LLVM_INCLUDE_DIRS})
add_definitions(${LLVM_DEFINITIONS})
message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")
message(STATUS "Using C_FLAGS: ${CMAKE_CXX_FLAGS}")

#find_package(jsoncpp REQUIRED)
#include_directories(${jsoncpp_INCLUDE_DIRS})
#link_libraries(${jsoncpp_LIBRARIES})


add_subdirectory(src/)
add_subdirectory(stdapi/capi)

#enable_testing()
#add_subdirectory(test/)
