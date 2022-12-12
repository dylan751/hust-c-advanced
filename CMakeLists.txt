add_executable(phone-bt phone-main.c)

add_subdirectory(cmake-btree)
target_link_libraries(phone-bt bt)