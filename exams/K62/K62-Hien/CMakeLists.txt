add_subdirectory(cgraph)
add_executable(K62 main.c)
target_link_libraries(K62 cgraph)