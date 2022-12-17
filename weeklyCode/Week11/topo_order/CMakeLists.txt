add_subdirectory(cgraph)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g")
add_executable(topo_order topo_order.c)
target_link_libraries(topo_order cgraph)
