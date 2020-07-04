add_subdirectory(ast)
add_subdirectory(lang)

add_executable(
        flare
        main.cpp
        ast/Node.cpp ast/Node.h)

target_link_libraries(flare ast lang)

llvm_map_components_to_libnames(llvm_libs core native mcjit)
target_link_libraries(flare ${llvm_libs})