add_subdirectory(cgraph)

add_executable(graph test.c)
target_link_libraries(graph cgraph)
