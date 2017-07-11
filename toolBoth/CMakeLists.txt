cmake_minimum_required(VERSION 2.6)
project(tollboth)

add_executable(tollboth main.cpp)

install(TARGETS tollboth RUNTIME DESTINATION bin)
