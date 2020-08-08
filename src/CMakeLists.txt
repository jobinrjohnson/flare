add_subdirectory(ast)
add_subdirectory(lang)
add_subdirectory(jit)

add_executable(
        flare
        main.cpp
        ast/Node.cpp ast/Node.h)

llvm_map_components_to_libnames(llvm_libs core native mcjit interpreter)
target_link_libraries(flare lang ast jit ${llvm_libs})