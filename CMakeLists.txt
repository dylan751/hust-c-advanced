add_subdirectory(cgraph)

add_executable(thiLopKhac main.c)
target_link_libraries(thiLopKhac cgraph)