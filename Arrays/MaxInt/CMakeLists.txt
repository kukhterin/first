cmake_minimum_required(VERSION 2.6)
project(maxint)

add_executable(maxint main.cpp)

install(TARGETS maxint RUNTIME DESTINATION bin)
