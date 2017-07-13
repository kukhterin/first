cmake_minimum_required(VERSION 2.6)
project(calc)

add_executable(calc main.cpp)

install(TARGETS calc RUNTIME DESTINATION bin)
