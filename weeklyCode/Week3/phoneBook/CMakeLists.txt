add_library(mylib STATIC 
    mylib.c utility.c)

add_executable(sort sort-main.c)
target_link_libraries(sort mylib)

add_executable(phone phone-demo.c phones-book.c)
target_link_libraries(phone mylib)
