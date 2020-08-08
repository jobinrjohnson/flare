include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_BINARY_DIR})

add_library(
        jit
        STATIC
        FlareJit.h FlareJit.cpp
)