add_executable(btsort btsort.c)
target_link_libraries(btsort ${BT_LIBS_LOCAL})

add_executable(btcopy btcopy.c)
target_link_libraries(btcopy ${BT_LIBS_LOCAL})