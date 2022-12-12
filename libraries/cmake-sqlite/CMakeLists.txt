project(demo-sqlite
        LANGUAGES C)
cmake_minimum_required(VERSION 2.6)
add_library(sqlite3 STATIC sqlite/sqlite3.c)

include_directories(sqlite)
add_executable(insert insert.c)
add_executable(select select.c)
foreach (example insert select)
  target_link_libraries(${example} sqlite3 pthread dl)
endforeach(example)