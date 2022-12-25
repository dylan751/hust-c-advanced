add_subdirectory(libfdr)

add_executable(K64 K64.c)
target_link_libraries(K64 fdr)