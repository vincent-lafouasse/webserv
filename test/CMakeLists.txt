cmake_minimum_required(VERSION 3.10)

project(webserv C CXX)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_C_STANDARD 23)
set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)

include(fetch_gtest.cmake)

set(ROOT ../)
set(tested_src_dir ${ROOT}/src/)
set(tested_include_dir ${tested_src_dir}/)

set(tested_files
)
list(TRANSFORM tested_files PREPEND ${tested_src_dir}/)

add_subdirectory(dummy_test)

include(CTest)
enable_testing()

add_test(NAME DummtTest
         COMMAND dummy_test)
