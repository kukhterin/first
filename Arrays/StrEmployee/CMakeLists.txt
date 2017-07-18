cmake_minimum_required(VERSION 2.6)
project(stremployee)

add_executable(stremployee main.cpp)

install(TARGETS stremployee RUNTIME DESTINATION bin)
