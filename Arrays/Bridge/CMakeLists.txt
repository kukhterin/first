cmake_minimum_required(VERSION 2.6)
project(bridge)

add_executable(bridge main.cpp)

install(TARGETS bridge RUNTIME DESTINATION bin)
