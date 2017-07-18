cmake_minimum_required(VERSION 2.6)
project(avginterval)

add_executable(avginterval main.cpp)

install(TARGETS avginterval RUNTIME DESTINATION bin)
