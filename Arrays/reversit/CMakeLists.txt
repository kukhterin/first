cmake_minimum_required(VERSION 2.6)
project(stringin)

add_executable(stringin main.cpp)

install(TARGETS stringin RUNTIME DESTINATION bin)
