include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_BINARY_DIR})

add_library(
        exceptions
        STATIC

        FlareException.cpp
        SemanticException.cpp
)