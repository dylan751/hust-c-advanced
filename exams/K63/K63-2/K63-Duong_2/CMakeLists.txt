add_subdirectory(cgraph)

add_executable(K63 K63.c)

target_link_libraries(K63 cgraph)