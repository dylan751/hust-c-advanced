add_library(mylib STATIC 
    mylib.c utility.c)

add_executable(sort sort-main.c)
target_link_libraries(sort mylib)

add_executable(phone phone-demo.c phones-book.c)
target_link_libraries(phone mylib)

add_subdirectory(libfdr)

add_executable(phone-fdr phone-book-fdr.c)
target_link_libraries(phone-fdr fdr)

