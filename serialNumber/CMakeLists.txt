cmake_minimum_required(VERSION 2.6)
project(serialnumber)

add_executable(serialnumber main.cpp)

install(TARGETS serialnumber RUNTIME DESTINATION bin)
