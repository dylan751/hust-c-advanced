add_subdirectory(libfdr)
add_executable(iqueue-demo iqueue-demo.c)
add_executable(iqueue-demo2 iqueue-demo2.c)
target_link_libraries(iqueue-demo fdr)
target_link_libraries(iqueue-demo2 fdr)

add_executable(stack istack.c)
target_link_libraries(stack fdr)