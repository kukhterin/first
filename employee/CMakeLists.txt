cmake_minimum_required(VERSION 2.6)
project(employee)

add_executable(employee main.cpp)

install(TARGETS employee RUNTIME DESTINATION bin)
