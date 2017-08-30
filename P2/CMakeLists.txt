cmake_minimum_required(VERSION 2.6)
project(p2)

add_executable(p2 main.cpp launcher.cpp)

install(TARGETS p2 RUNTIME DESTINATION bin)
