add_subdirectory(cgraph)

add_executable(K61 K61.c)
target_link_libraries(K61 cgraph)