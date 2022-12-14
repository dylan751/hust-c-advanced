add_subdirectory(cgraph)

add_executable(graph1 g1-main.c)

target_link_libraries(graph1 cgraph)