project(btree
        LANGUAGES C)
cmake_minimum_required(VERSION 2.8)
option(LFS "To build LFS version of bt" OFF)
option(ORIGINAL_EXECUTABLE "Build original executable from the library" OFF)

include_directories(inc)

if (LFS)
  set(BT_LFS_FLAG "-D_FILE_OFFSET_BITS=64")
endif (LFS)

if (EXISTS "/usr/include/readline")
  set(BT_RDLINE_FLAG "-DREADLINE")
  set(BT_RDLINE_LIB "-lreadline")
endif ()

AUX_SOURCE_DIRECTORY(src-lib BT_SRC)

set(BT_CFLAGS "-pedantic-errors -Wall -Wno-long-long ${BT_LFS_FLAG} ${BT_RDLINE_FLAG}")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${BT_CFLAGS}")

# message(STATUS "BT_SRC: ${BT_SRC} \n RDLINE: ${BT_RDLINE_LIB} ${BT_RDLINE_FLAG}")

add_library(bt STATIC ${BT_SRC})
set(BT_LIBS_LOCAL bt ${BT_RDLINE_LIB})
set(BT_LIBS ${BT_LIBS_LOCAL} PARENT_SCOPE)

if (ORIGINAL_EXECUTABLE)
  add_executable(bt-bin src-main/bt.c src-main/btcmd.c)
  set_target_properties(bt-bin PROPERTIES OUTPUT_NAME bt)
  add_executable(kcp src-main/kcp.c)
  add_executable(btr src-main/btr.c)
  add_executable(bigt src-main/bigt.c)
  add_executable(bigtdel src-main/bigtdel.c)
  add_executable(corrupt Testcases/corrupt.c)

  foreach (name bt-bin kcp btr bigt bigtdel corrupt)
    target_link_libraries(${name} ${BT_LIBS_LOCAL})
  endforeach(name)

  add_subdirectory(samples)
endif (ORIGINAL_EXECUTABLE)
