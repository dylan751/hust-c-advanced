add_executable(vector main.c)

add_subdirectory(cgraph)

add_executable(ivec ivec-main.c )
target_link_libraries(ivec cgraph)
