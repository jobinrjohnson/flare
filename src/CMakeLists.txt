include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_subdirectory(ast)
add_subdirectory(lang)
add_subdirectory(jit)
add_subdirectory(exceptions)
add_subdirectory(types)

add_executable(
        flare
        main.cpp
        flare.cpp flare.h)

llvm_map_components_to_libnames(llvm_libs core native mcjit interpreter)
target_link_libraries(flare pthread lang ast jit exceptions types jsoncpp ${llvm_libs})

add_custom_command(TARGET flare
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:flare> ../)