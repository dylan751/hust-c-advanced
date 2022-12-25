add_subdirectory(cgraph)

add_executable(thiLopKhac thiLopKhac.c)
target_link_libraries(thiLopKhac cgraph)