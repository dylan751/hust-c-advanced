add_subdirectory(cgraph)

add_executable(bfs-demo-main bfs-demo-main.c)
target_link_libraries(bfs-demo-main cgraph)