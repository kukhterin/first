cmake_minimum_required(VERSION 2.6)
project(fraction)

add_executable(fraction main.cpp)

install(TARGETS fraction RUNTIME DESTINATION bin)
