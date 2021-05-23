include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_subdirectory(ast)
add_subdirectory(lang)
add_subdirectory(jit)
add_subdirectory(exceptions)

add_executable(
        flare
        main.cpp
)

llvm_map_components_to_libnames(llvm_libs core native mcjit interpreter)
target_link_libraries(flare lang ast jit exceptions ${llvm_libs})