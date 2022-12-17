add_subdirectory(cgraph)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g")
add_executable(dijkstra dijkstra.c)
target_link_libraries(dijkstra cgraph)


