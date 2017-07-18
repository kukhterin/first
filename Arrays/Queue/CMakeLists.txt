cmake_minimum_required(VERSION 2.6)
project(queue)

add_executable(queue main.cpp)

install(TARGETS queue RUNTIME DESTINATION bin)
