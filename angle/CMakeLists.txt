cmake_minimum_required(VERSION 2.6)
project(angle)

add_executable(angle main.cpp)

install(TARGETS angle RUNTIME DESTINATION bin)
