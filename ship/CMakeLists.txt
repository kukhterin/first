cmake_minimum_required(VERSION 2.6)
project(ship)

add_executable(ship main.cpp)

install(TARGETS ship RUNTIME DESTINATION bin)
