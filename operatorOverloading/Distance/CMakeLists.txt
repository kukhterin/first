cmake_minimum_required(VERSION 2.6)
project(distance)

add_executable(distance main.cpp Distance.cpp)

install(TARGETS distance RUNTIME DESTINATION bin)
