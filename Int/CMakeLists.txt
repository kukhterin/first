cmake_minimum_required(VERSION 2.6)
project(int)

add_executable(int main.cpp)

install(TARGETS int RUNTIME DESTINATION bin)
