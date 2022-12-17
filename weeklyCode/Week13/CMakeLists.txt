add_subdirectory(cgraph)
add_executable(baiTap baiTap.c)
target_link_libraries(baiTap cgraph)

add_executable(Long main.c)
target_link_libraries(Long cgraph)