cmake_minimum_required(VERSION 2.6)
project(salary)

add_executable(salary main.cpp Employees.cpp)

install(TARGETS salary RUNTIME DESTINATION bin)
