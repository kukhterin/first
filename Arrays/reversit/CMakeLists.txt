cmake_minimum_required(VERSION 2.6)
project(reverse)

add_executable(reverse main.cpp test.cpp reverseIt.cpp)

install(TARGETS reverse RUNTIME DESTINATION bin)
