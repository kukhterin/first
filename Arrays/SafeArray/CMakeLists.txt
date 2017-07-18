cmake_minimum_required(VERSION 2.6)
project(safearray)

add_executable(safearray main.cpp)

install(TARGETS safearray RUNTIME DESTINATION bin)
