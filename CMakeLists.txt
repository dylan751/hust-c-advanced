add_subdirectory(libfdr)


add_executable(de20192 de20192.c)
add_executable(de20182 de20182.c)

target_link_libraries(de20192 fdr)
target_link_libraries(de20182 fdr)
