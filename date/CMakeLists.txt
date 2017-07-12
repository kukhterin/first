cmake_minimum_required(VERSION 2.6)
project(date)

add_executable(date main.cpp)

install(TARGETS date RUNTIME DESTINATION bin)
