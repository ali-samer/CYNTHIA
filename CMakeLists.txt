cmake_minimum_required( VERSION 3.2 )
set( CMAKE_CXX_STANDARD 17 )
project( CYNTHIA )

include_directories(src)

add_executable(CYNTHIA main.cpp)