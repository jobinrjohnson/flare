include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_BINARY_DIR})
include_directories(${CMAKE_SOURCE_DIR}/src)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -I/usr/local/opt/flex/include")

find_package(BISON)
find_package(FLEX)

bison_target(Parser parser.yy ${CMAKE_CURRENT_BINARY_DIR}/parser.cc)
flex_target(Scanner scanner.ll ${CMAKE_CURRENT_BINARY_DIR}/scanner.cc)

set_source_files_properties(${CMAKE_CURRENT_BINARY_DIR}/scanner.cc PROPERTIES COMPILE_FLAGS -Wno-unused-parameter)

add_flex_bison_dependency(Scanner Parser)

add_library(lang
        STATIC
        ${FLEX_Scanner_OUTPUTS}
        ${BISON_Parser_OUTPUTS}
        scanner.h
        driver.cpp driver.h)