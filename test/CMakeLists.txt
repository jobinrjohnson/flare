include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../src)

add_library(
        test_base
        STATIC
        ../src/flare.cpp
)

llvm_map_components_to_libnames(llvm_libs core native mcjit interpreter)
set(libs "test_base" "lang" "ast" "jit" "exceptions" ${llvm_libs})

# Test : SimpleArithmetic
add_executable(SimpleArithmetic SimpleArithmetic.cpp)
target_link_libraries(SimpleArithmetic ${libs})
add_test(SimpleArithmetic SimpleArithmetic)

# Test : Logical Ops
add_executable(LogicalOpsTest LogicalOpsTest.cpp)
target_link_libraries(LogicalOpsTest ${libs})
add_test(LogicalOpsTest LogicalOpsTest)
