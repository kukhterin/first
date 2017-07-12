cmake_minimum_required(VERSION 2.6)
project(temp)

add_executable(temp main.cpp)

install(TARGETS temp RUNTIME DESTINATION bin)
