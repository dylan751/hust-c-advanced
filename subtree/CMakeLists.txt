add_executable(subtree subtree-main.c)

add_subdirectory(libfdr)
target_link_libraries(subtree fdr)