cmake_minimum_required(VERSION 2.6)
project(reverseit)

add_executable(reverseit main.cpp)

install(TARGETS reverseit RUNTIME DESTINATION bin)
